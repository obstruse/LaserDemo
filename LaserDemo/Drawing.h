// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#ifndef DRAWING_H
#define DRAWING_H

#include "Laser.h"
extern Laser laser;

//! Allows to draw text and objects from PROGMEM.
class Drawing
{
public:
  // draw these points
  int points = 0;
  int * pX;
  int * pY;

  // calculated KPPS from last drawObject
  int calcKPPS = 0;
  unsigned long ms = 0;
  int positions = 0;

  //! Draws the given string at x,y position. 
  void drawString(String text, int x, int y );

  //! Draws the given character, returns the x advance...
  long drawCharacter(byte character, long X = 0, long Y = 0);

  //! Get X advance for given char
  long advance(byte character);

  //! Get X advance for string
  long stringAdvance(String text);

  //! Draws the given data (which needs to be in PROGMEM). Size indicates the number
  //! of draw commands (so it is sizeof(data)/4).
  void drawObject(const uint32_t* data, int size, long X = 0, long Y = 0);

  //! Draws the given data (which needs to be in PROGMEM). Size indicates the number
  //! of draw commands (so it is sizeof(data)/4).
  void drawObjectRotated(const unsigned short* data, int size, long centerX, long centerY, int angle);

  //! Draws the object and rotates in 3D. 
  void drawObjectRotated3D(const unsigned short* data, int size, long centerX, long centerY, int angleX, int angleY, int fov);

  //! Returns the center of the object (center of bounding box)
  void calcObjectBox(const unsigned short* data, int size, long& centerX, long& centerY, long& width, long& height);

private:
  // maximum X position reached by object
  int maxXpos = 0;

};

#endif
