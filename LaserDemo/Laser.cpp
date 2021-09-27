// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#include "Laser.h"

int laserPoints = 0;

Laser::Laser(int laserPin) {
  _last_scan = 0;
  
  _laserPin = laserPin;
  FPquality = FROM_INT(LASER_QUALITY);

  FPx0 = 0;
  FPy0 = 0;

  _state = 0;
  
  FPscale = FROM_INT(1);
  FPoffsetX = 0;
  FPoffsetY = 0;

  setOptions(SCANNER_KPPS, LASER_TOGGLE_DELAY, LASER_QUALITY);
}

void Laser::init() { 
  pinMode (SS_PIN, OUTPUT);
  pinMode (LDAC_PIN, OUTPUT);

  digitalWrite (SS_PIN, HIGH);
  digitalWrite (LDAC_PIN, LOW);

  SPI.begin();
  SPI.beginTransaction (SPISettings (20000000L, MSBFIRST, SPI_MODE0));  //MCP4922 supports 20MHz clock
  pinMode(_laserPin, OUTPUT);
}

void Laser::sendToDAC(int x, int y) {

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

  laserPoints++;

  scanner_throttle();

  x1 &= 0xfff;
  GPOC = (1<<SS_PIN);
  SPI.transfer((x1 >> 8) | commandBits1);
  SPI.transfer((x1 & 0xff));
  GPOS = (1<<SS_PIN);

  y1 &= 0xfff;
  GPOC = (1<<SS_PIN);
  SPI.transfer((y1 >> 8) | commandBits2);
  SPI.transfer((y1 & 0xff));
  GPOS = (1<<SS_PIN);

  // latch
  GPOC = (1<<LDAC_PIN);
  GPOS = (1<<LDAC_PIN);
}

void Laser::sendto (long xpos, long ypos) {
  //! calculate FPnew position
  // FPscale is (float)scale shifted to fixpont, so the result of the multiply is scaled AND shifted to fixpoint
  // the scaling will add some fractional junk, so that is masked out
  FIXPT FPx = ((xpos * FPscale) + FPoffsetX) & FPMASK;
  FIXPT FPy = ((ypos * FPscale) + FPoffsetY) & FPMASK;

  //! calculate FPdistance to move
  FIXPT FPdistX = FPx - FPx0;
  FIXPT FPdistY = FPy - FPy0;

  //! loop: if either XorY abs(FPdistance ) > FPquality distance, FPdistance/2 for both
  while (abs(FPdistX) > FPquality || abs(FPdistY) > FPquality) {
    FPdistX /= 2;
    FPdistY /= 2;
  }

  //! loop:  add increment and send to DAC
  while (FPx0 != FPx || FPy0 != FPy) {    // seems risky? That's why the FPMASK above...
    FPx0 += FPdistX;
    FPy0 += FPdistY;
    sendToDAC(TO_INT(FPx0), TO_INT(FPy0));
  }

  // special case: new point same position as last point
  // need to send to DAC anyway for timing reasons
  if ( FPdistX == 0 && FPdistY == 0 ) {
    sendToDAC(TO_INT(FPx0), TO_INT(FPy0));
  }
}

void Laser::on() {
  if (!_state) {
    _state = 1;
    ttlQueue[ttlNow] = 1;
  }
}

void Laser::off() {
  if (_state) {
    _state = 0;
    ttlQueue[ttlNow] = 0;
  }
}

unsigned long nextYield;
void Laser::scanner_throttle() {
  int ttlAction;
  int ttlThen;

  ttlThen = (ttlNow 
            - ttlCourse
            + 16) & 0xf;

  ttlAction = ttlQueue[ttlThen];
  if (ttlAction >= 0) {
    delayMicroseconds(ttlFine);
    if (ttlAction) GPOS = (1<<_laserPin);
    else           GPOC = (1<<_laserPin);
  } 
  
  if (nextYield < millis()) {
    yield();
    nextYield = millis() + 1000;
  } 
  
  while (_last_scan + (1000/SCANNER_KPPS) > micros() );

  ttlNow = (ttlNow + 1) & 0xf;
  ttlQueue[ttlNow] = -1;
  
  _last_scan = micros();
}


void Laser::setOptions(int kpps, int ltd, int lq) {
  if ( kpps ) { SCANNER_KPPS = kpps; }
  if ( ltd )  { LASER_TOGGLE_DELAY = ltd; }
  if ( lq )   { LASER_QUALITY = lq; }

  ttlCourse = ceil(LASER_TOGGLE_DELAY * SCANNER_KPPS / 1000.0);
  ttlFine   = LASER_TOGGLE_DELAY - (ttlCourse - 1) * 1000.0 / SCANNER_KPPS;

  FPquality = FROM_INT(LASER_QUALITY);
}

void Laser::setScale(float scale) { 
  FPscale = FROM_FLOAT(scale);
}

void Laser::setOffset(long offsetX, long offsetY) { 
  FPoffsetX = FROM_INT(offsetX);
  FPoffsetY = FROM_INT(offsetY);
}

