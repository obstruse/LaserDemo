// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#ifndef LASER_H
#define LASER_H

#include "Arduino.h"
#include "Basics.h"

#include <SPI.h>

// laser TTL on pin 4
#define LDAC_PIN 5
#define SS_PIN 15

#define MOSI  13
#define MISO  12    // not used
#define SCK   14

// command bits for MCP4922
#define commandBits1 B00110000    // |DACa|Unbuffered|1x gain|Active Mode|4 high bits data| next byte | 8 low bits data|
#define commandBits2 B10110000    // |DACb|Unbuffered|1x gain|Active Mode|4 high bits data| next byte | 8 low bits data|

extern int laserPoints;

// -- The following flags can be used to rotate/flip the output without changing the DAC wiring, just uncomment the desired swap/flip
// define this to swap X and Y on the DAC
//#define LASER_SWAP_XY
// define this to flip along the x axis
//#define LASER_FLIP_X
// define this to flip along the y axis
#define LASER_FLIP_Y

//! Encapsulates the laser movement and on/off state.
class Laser
{
public:
  //! The laser is initialized with the laserPin,
  //! which selects the digital pin that turns the laser pointer on/off.
  Laser(int laserPin);

  
  void init();

  //! send the laser to the given position, scaled and translated and line clipped.
  void sendto(long x, long y);
  
  void flush();
  
  void wait(long length);

  void on();
  void off();
  
  void setScale(float scale);
  void setOffset(long offsetX, long offsetY);
  
  void setOptions(int kpps, int ltd, int lq);
  void getOptions(int &kpps, int &ltd, int &lq) { kpps = SCANNER_KPPS; ltd = LASER_TOGGLE_DELAY; lq = LASER_QUALITY; }
  
  //! send X/Y to DAC
  void sendToDAC(int x, int y);

private:

  int ttlNow = 0;
  int ttlThen = 0;
  int ttlQueue[16];

  int ttlCourse;
  int ttlFine;

  int SCANNER_KPPS = 20;
  int LASER_TOGGLE_DELAY = 120;
  int LASER_QUALITY = 4096; // maximum length of line segment before prog splits it into chunks.  default to OFF



//! send X/Y to DAC
////  void sendToDAC(int x, int y);

  //! computes the out code for line clipping
  int computeOutCode(long x, long y);
  //! returns if the line should be drawn, clips line to clip area
  bool clipLine(long& x0, long& y0, long& x1, long& y1);

  void scanner_throttle();
  unsigned long _last_scan;

  int _laserPin;

  FIXPT FPquality;

  // current x position
  FIXPT FPx0;   
  // current y position
  FIXPT FPy0;
  int  _state;

  FIXPT FPscale;
  FIXPT FPoffsetX;
  FIXPT FPoffsetY;

};

#endif
