// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#include "Laser.h"

// these values can be adapted to fine tune sendto:

// if this is enabled, pins need to be 10 and 7 in dac init below, but it is a big speedup!
#define MCP4X_PORT_WRITE 1

/*
 * doing it manually, since two single DACs didn't work with library.
 * ...and there was the PORTx stuff...
#include "DAC_MCP4X.h"
MCP4X dac;
*/

int laserPoints = 0;

//void laserToggleOn();
//void laserToggleOff();

//int ttlPin;


Laser::Laser(int laserPin)
{
  _last_scan = 0;
  
  _laserPin = laserPin;
  _quality = FROM_FLOAT(1./(LASER_QUALITY));

  _x = 0;
  _y = 0;
  _oldX = 0;
  _oldY = 0;

  _state = 0;
  
  _scale = 1;
  _offsetX = 0;
  _offsetY = 0;

  _moved = 0;
  _maxMove = -1;
  _laserForceOff = false;
  resetClipArea();

  _enable3D = false;
  _zDist = 1000;

  setOptions(SCANNER_KPPS, LASER_TOGGLE_DELAY, LASER_QUALITY);

}

void Laser::init()
{

/*
  // laser toggle timer
  timer2_isr_init();
  timer2_attachInterrupt(laserToggleOff);
  timer2_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);

  timer1_isr_init();
  timer1_attachInterrupt(laserToggleOn);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);

  ttlPin = _laserPin;
  */
  
/***************** DAC *************************/
  // Serial.println("...init");
  pinMode (SS_PIN, OUTPUT);
  pinMode (LDAC_PIN, OUTPUT);

  digitalWrite (SS_PIN, HIGH);
//  digitalWrite (LDAC_PIN, HIGH);
  digitalWrite (LDAC_PIN, LOW);

  SPI.begin();
  SPI.beginTransaction (SPISettings (4000000, MSBFIRST, SPI_MODE0));
/***********************************************/

//  dac.init(MCP4X_4822, 5000, 5000,
//      10, 7, 1);
//  dac.setGain2x(MCP4X_CHAN_A, 0);
//  dac.setGain2x(MCP4X_CHAN_B, 0);
//  dac.begin(1);
 
  pinMode(_laserPin, OUTPUT);

  // Serial.println("done init");
}

void Laser::sendToDAC(int x, int y)
{
  // Serial.println("sendtoDAC");
  #ifdef LASER_SWAP_XY
  int x1 = y;
  int y1 = x;
  #else
  int x1 = x;
  int y1 = y;
  #endif
  #ifdef LASER_FLIP_X
  x1 = 4095 - x1;
  #endif
  #ifdef LASER_FLIP_Y
  y1 = 4095 - y1;
  #endif

//  dac.output2(x1, y1);

  laserPoints++;

  scanner_throttle();

  x1 &= 0xfff;
  digitalWrite (SS_PIN, LOW);
  SPI.transfer((x1 >> 8) | commandBits1);
  SPI.transfer((x1 & 0xff));
  digitalWrite (SS_PIN, HIGH);

  y1 &= 0xfff;
  digitalWrite (SS_PIN, LOW);
  SPI.transfer((y1 >> 8) | commandBits2);
  SPI.transfer((y1 & 0xff));
  digitalWrite (SS_PIN, HIGH);

  // latch
  digitalWrite (LDAC_PIN, LOW);
  digitalWrite (LDAC_PIN, HIGH);

//  wait(laser_throttle);
  
}

void Laser::resetClipArea()
{
  _clipXMin = 0;
  _clipYMin = 0;
  _clipXMax = 4095;
  _clipYMax = 4095;
}

void Laser::setClipArea(long x, long y, long x1, long y1)
{
  _clipXMin = x;
  _clipYMin = y;
  _clipXMax = x1;
  _clipYMax = y1;
}

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int Laser::computeOutCode(long x, long y)
{
  int code = INSIDE;          // initialised as being inside of [[clip window]]

  if (x < _clipXMin)           // to the left of clip window
    code |= LEFT;
  else if (x > _clipXMax)      // to the right of clip window
    code |= RIGHT;
  if (y < _clipYMin)           // below the clip window
    code |= BOTTOM;
  else if (y > _clipYMax)      // above the clip window
    code |= TOP;

  return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (_clipXMin, _clipYMin) to (_clipXMax, _clipYMax).
bool Laser::clipLine(long& x0, long& y0, long& x1, long& y1)
{
  // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
  int outcode0 = computeOutCode(x0, y0);
  int outcode1 = computeOutCode(x1, y1);
  bool accept = false;
  
  while (true) {
    if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
      accept = true;
      break;
    } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
      break;
    } else {
      // failed both tests, so calculate the line segment to clip
      // from an outside point to an intersection with clip edge
      long x, y;

      // At least one endpoint is outside the clip rectangle; pick it.
      int outcodeOut = outcode0 ? outcode0 : outcode1;

      // Now find the intersection point;
      // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
      if (outcodeOut & TOP) {           // point is above the clip rectangle
        x = x0 + (x1 - x0) * float(_clipYMax - y0) / float(y1 - y0);
        y = _clipYMax;
      } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
        x = x0 + (x1 - x0) * float(_clipYMin - y0) / float(y1 - y0);
        y = _clipYMin;
      } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
        y = y0 + (y1 - y0) * float(_clipXMax - x0) / float(x1 - x0);
        x = _clipXMax;
      } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
        y = y0 + (y1 - y0) * float(_clipXMin - x0) / float(x1 - x0);
        x = _clipXMin;
      }

      // Now we move outside point to intersection point to clip
      // and get ready for next pass.
      if (outcodeOut == outcode0) {
        x0 = x;
        y0 = y;
        outcode0 = computeOutCode(x0, y0);
      } else {
        x1 = x;
        y1 = y;
        outcode1 = computeOutCode(x1, y1);
      }
    }
  }
  return accept;
}

void Laser::sendto (long xpos, long ypos)
{
//   Serial.println("sendto");
  if (_enable3D) {
    Vector3i p1;
    Vector3i p;
    p1.x = xpos;
    p1.y = ypos;
    p1.z = 0;
    Matrix3::applyMatrix(_matrix, p1, p);
    xpos = ((_zDist*(long)p.x) / (_zDist + (long)p.z)) + 2048;
    ypos = ((_zDist*(long)p.y) / (_zDist + (long)p.z)) + 2048;
  }
  // Float was too slow on Arduino, so I used
  // fixed point precision here:
  long xNew = TO_INT(xpos * _scale) + _offsetX;
  long yNew = TO_INT(ypos * _scale) + _offsetY;
  long clipX = xNew;
  long clipY = yNew;
  long oldX = _oldX;
  long oldY = _oldY;
  if (clipLine(oldX,oldY, clipX,clipY)) {
    if (oldX != _oldX || oldY != _oldY) {
//    Serial.print ("...st.1 ");
//    Serial.println (oldX);
      sendtoRaw(oldX, oldY);
    }
//    Serial.print ("...st.2 ");
//    Serial.println (clipX);
    sendtoRaw(clipX, clipY);
  }
  _oldX = xNew;
  _oldY = yNew;
}

void Laser::sendtoRaw (long xNew, long yNew)
{
  // Serial.println("sendtoRaw");
  // devide into equal parts, using _quality
  long fdiffx = xNew - _x;
  long fdiffy = yNew - _y;
  long diffx = TO_INT(abs(fdiffx) * _quality); 
  long diffy = TO_INT(abs(fdiffy) * _quality);

  // store movement for max move
  long moved = _moved;
  _moved += abs(fdiffx) + abs(fdiffy);

  // use the bigger direction
  if (diffx < diffy) 
  {
    diffx = diffy;     
  }
  // Serial.println("str...0");
  // Serial.println(diffx);
  if (diffx == 0 ) {
    fdiffx = 0;
    fdiffy = 0;
  } else {
    fdiffx = FROM_INT(fdiffx) / diffx;
    fdiffy = FROM_INT(fdiffy) / diffx;
  }
  // interpolate in FIXPT
  // Serial.println("str...0.1");
  FIXPT tmpx = 0;
  FIXPT tmpy = 0;
  // Serial.println("str...1");
  for (int i = 0; i<diffx-1;i++) 
  {
  // Serial.println("str...1.1");
    // for max move, stop inside of line if required...
    if (_maxMove != -1) {
      long moved2 = moved + abs(TO_INT(tmpx)) + abs(TO_INT(tmpy));
      if (!_laserForceOff && moved2 > _maxMove) {
        off();
        _laserForceOff = true;
        _maxMoveX = _x + TO_INT(tmpx);
        _maxMoveY = _y + TO_INT(tmpy);
      }
    } 
    tmpx += fdiffx;
    tmpy += fdiffy;
//   Serial.print("str...2 ");
//   Serial.println (_x + TO_INT(tmpx));
    sendToDAC(_x + TO_INT(tmpx), _y + TO_INT(tmpy));
    #ifdef LASER_MOVE_DELAY
    wait(LASER_MOVE_DELAY);
    #endif
  }
  // Serial.println("str...2.1");
  
  // for max move, stop if required...
  if (!_laserForceOff && _maxMove != -1 && _moved > _maxMove) {
    off();
    _laserForceOff = true;
    _maxMoveX = xNew;
    _maxMoveY = yNew;
  }

  _x = xNew;
  _y = yNew;
//     Serial.print("str...3 ");
//     Serial.println (_x);
  sendToDAC(_x, _y);
//  wait(LASER_END_DELAY);
}

void Laser::drawline(long x1, long y1, long x2, long y2)
{
  if (_x != x1 or _y != y1) 
  {
    off();
    sendto(x1,y1);
  }
  on();
  sendto(x2,y2);
  wait(LASER_LINE_END_DELAY);
}

void Laser::on()
{
  if (!_state && !_laserForceOff) 
  {
    _state = 1;
    ttlQueue[ttlNow] = 1;
  }
}

void Laser::off()
{
  if (_state) 
  {
    _state = 0;
    ttlQueue[ttlNow] = 0;
  }
}

void Laser::scanner_throttle() {

  int ttlAction;
  int ttlThen;

  ttlThen = (ttlNow 
            - ttlCourse
            + 16) & 0xf;

  ttlAction = ttlQueue[ttlThen];

  if (ttlAction >= 0) {
      delayMicroseconds(ttlFine);
      digitalWrite(_laserPin, ttlAction);
      ttlAction = -1;
      yield();
    } 
  
  while (_last_scan + (1000/SCANNER_KPPS) > micros() );

  ttlNow = ++ttlNow & 0xf;
  ttlQueue[ttlNow] = -1;
  
  _last_scan = micros();

}

/*
void Laser::scanner_throttle() {

  int ttlAction;
  int ttlThen;
  unsigned int tempTime;
  
  char temp[200];

  ttlThen = (ttlNow 
            - ttlCourse
            + 16) & 0xf;

  ttlAction = ttlQueue[ttlThen];

  do {
    tempTime = micros();
    if (ttlAction >= 0  && _last_scan + ttlFine <= tempTime) {
      digitalWrite(_laserPin, ttlAction);
      ttlAction = -1;
    } 
    yield(); 
  } while (_last_scan + (1000/SCANNER_KPPS) > tempTime);

  ttlNow = ++ttlNow & 0xf;
  ttlQueue[ttlNow] = -1;
  
  _last_scan = micros();

}
*/
/*
void Laser::scanner_throttle() {
  while (_last_scan + (1000/SCANNER_KPPS) > micros());
  _last_scan = micros();

  ttlThen = (ttlNow - (LASER_TOGGLE_DELAY * SCANNER_KPPS / 1000) + 16) & 0xf;
  if (ttlQueue[ttlThen] >= 0) {
    digitalWrite(_laserPin, ttlQueue[ttlThen]);
    yield();
  }
  ttlNow = ++ttlNow & 0xf;
  ttlQueue[ttlNow] = -1;
}
*/
void Laser::setOptions(int kpps, int ltd, int lq) {

  if ( kpps ) { SCANNER_KPPS = kpps; }
  if ( ltd )  { LASER_TOGGLE_DELAY = ltd; }
  if ( lq )   { LASER_QUALITY = lq; }

  ttlCourse = ceil(LASER_TOGGLE_DELAY * SCANNER_KPPS / 1000.0);
  ttlFine   = LASER_TOGGLE_DELAY - (ttlCourse - 1) * 1000.0 / SCANNER_KPPS;

  _quality = FROM_FLOAT(1./(LASER_QUALITY));

}

void Laser::wait(long length)
{
  delayMicroseconds(length);
}

void Laser::setScale(float scale)
{ 
  _scale = FROM_FLOAT(scale);
}

void Laser::setOffset(long offsetX, long offsetY)
{ 
  _offsetX = offsetX;
  _offsetY = offsetY;
}

/*
void laserToggleOn() {
    digitalWrite(ttlPin,HIGH);
}

void laserToggleOff() {
  digitalWrite(ttlPin,LOW);  
}
*/
