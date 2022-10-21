// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#include "Drawing.h"
//#include "Font2.h"
#include "font_nv202.h"


//---------------------------------------------------------------

//! Draws the given string at x,y position. 
void Drawing::drawString(String text, int x, int y ) {
  int i = 0;
  int x1 = x;
  while (text.charAt(i) != '\0')
  {
      x1 += drawCharacter(text.charAt(i), x1, y); 
      i ++;
  }
}


//---------------------------------------------------------------

// draw character at location X,Y
// returns X value to the right of the character (plus padding)
long Drawing::drawCharacter(byte character, long X, long Y)
{
  maxXpos = 0;

  switch (character)
  {
    case 'A': drawObject(font_32, sizeof(font_32)/4, X, Y); break;
    case 'B': drawObject(font_33, sizeof(font_33)/4, X, Y); break;
    case 'C': drawObject(font_34, sizeof(font_34)/4, X, Y); break;
    case 'D': drawObject(font_35, sizeof(font_35)/4, X, Y); break;
    case 'E': drawObject(font_36, sizeof(font_36)/4, X, Y); break;
    case 'F': drawObject(font_37, sizeof(font_37)/4, X, Y); break;
    case 'G': drawObject(font_38, sizeof(font_38)/4, X, Y); break;
    case 'H': drawObject(font_39, sizeof(font_39)/4, X, Y); break;
    case 'I': drawObject(font_40, sizeof(font_40)/4, X, Y); break;
    case 'J': drawObject(font_41, sizeof(font_41)/4, X, Y); break;
    case 'K': drawObject(font_42, sizeof(font_42)/4, X, Y); break;
    case 'L': drawObject(font_43, sizeof(font_43)/4, X, Y); break;
    case 'M': drawObject(font_44, sizeof(font_44)/4, X, Y); break;
    case 'N': drawObject(font_45, sizeof(font_45)/4, X, Y); break;
    case 'O': drawObject(font_46, sizeof(font_46)/4, X, Y); break;
    case 'P': drawObject(font_47, sizeof(font_47)/4, X, Y); break;
    case 'Q': drawObject(font_48, sizeof(font_48)/4, X, Y); break;
    case 'R': drawObject(font_49, sizeof(font_49)/4, X, Y); break;
    case 'S': drawObject(font_50, sizeof(font_50)/4, X, Y); break;
    case 'T': drawObject(font_51, sizeof(font_51)/4, X, Y); break;
    case 'U': drawObject(font_52, sizeof(font_52)/4, X, Y); break;
    case 'V': drawObject(font_53, sizeof(font_53)/4, X, Y); break;
    case 'W': drawObject(font_54, sizeof(font_54)/4, X, Y); break;
    case 'X': drawObject(font_55, sizeof(font_55)/4, X, Y); break;
    case 'Y': drawObject(font_56, sizeof(font_56)/4, X, Y); break;
    case 'Z': drawObject(font_57, sizeof(font_57)/4, X, Y); break;
    
    case 'a': drawObject(font_64, sizeof(font_64)/4, X, Y); break;
    case 'b': drawObject(font_65, sizeof(font_65)/4, X, Y); break;
    case 'c': drawObject(font_66, sizeof(font_66)/4, X, Y); break;
    case 'd': drawObject(font_67, sizeof(font_67)/4, X, Y); break;
    case 'e': drawObject(font_68, sizeof(font_68)/4, X, Y); break;
    case 'f': drawObject(font_69, sizeof(font_69)/4, X, Y); break;
    case 'g': drawObject(font_70, sizeof(font_70)/4, X, Y); break;
    case 'h': drawObject(font_71, sizeof(font_71)/4, X, Y); break;
    case 'i': drawObject(font_72, sizeof(font_72)/4, X, Y); break;
    case 'j': drawObject(font_73, sizeof(font_73)/4, X, Y); break;
    case 'k': drawObject(font_74, sizeof(font_74)/4, X, Y); break;
    case 'l': drawObject(font_75, sizeof(font_75)/4, X, Y); break;
    case 'm': drawObject(font_76, sizeof(font_76)/4, X, Y); break;
    case 'n': drawObject(font_77, sizeof(font_77)/4, X, Y); break;
    case 'o': drawObject(font_78, sizeof(font_78)/4, X, Y); break;
    case 'p': drawObject(font_79, sizeof(font_79)/4, X, Y); break;
    case 'q': drawObject(font_80, sizeof(font_80)/4, X, Y); break;
    case 'r': drawObject(font_81, sizeof(font_81)/4, X, Y); break;
    case 's': drawObject(font_82, sizeof(font_82)/4, X, Y); break;
    case 't': drawObject(font_83, sizeof(font_83)/4, X, Y); break;
    case 'u': drawObject(font_84, sizeof(font_84)/4, X, Y); break;
    case 'v': drawObject(font_85, sizeof(font_85)/4, X, Y); break;
    case 'w': drawObject(font_86, sizeof(font_86)/4, X, Y); break;
    case 'x': drawObject(font_87, sizeof(font_87)/4, X, Y); break;
    case 'y': drawObject(font_88, sizeof(font_88)/4, X, Y); break;
    case 'z': drawObject(font_89, sizeof(font_89)/4, X, Y); break;
    
    case '0': drawObject(font_15, sizeof(font_15)/4, X, Y); break;
    case '1': drawObject(font_16, sizeof(font_16)/4, X, Y); break;
    case '2': drawObject(font_17, sizeof(font_17)/4, X, Y); break;
    case '3': drawObject(font_18, sizeof(font_18)/4, X, Y); break;
    case '4': drawObject(font_19, sizeof(font_19)/4, X, Y); break;
    case '5': drawObject(font_20, sizeof(font_20)/4, X, Y); break;
    case '6': drawObject(font_21, sizeof(font_21)/4, X, Y); break;
    case '7': drawObject(font_22, sizeof(font_22)/4, X, Y); break;
    case '8': drawObject(font_23, sizeof(font_23)/4, X, Y); break;
    case '9': drawObject(font_24, sizeof(font_24)/4, X, Y); break;
    case '!': drawObject(font_0,  sizeof(font_0)/4,  X, Y); break;
    case '?': drawObject(font_30, sizeof(font_30)/4, X, Y); break;
    case '.': drawObject(font_13, sizeof(font_13)/4, X, Y); break;
    case ' ': maxXpos = X + 700; break;

  }

  return maxXpos + 200;
}

//---------------------------------------------------------------

void Drawing::drawObject(const uint32_t* data, int size, long X, long Y)
{
  // calculate KPPS
  unsigned long startTime = millis()-1;
  laser.Points = 0;

  // Serial.println("drawobject");
  const uint32_t* d = data;
  unsigned int posX;
  unsigned int posY;
  unsigned int posXY;

  // sendToDAC() - direct to galvos
  // sendto()    - scaling + (clipping) + Laser Quality

  // give the mirrors time to get to the first position...before turning on laser
  posXY = pgm_read_dword(d);
  posX = posXY >> 16;
  posY = posXY & 0xffff;
  laser.sendto((posX & 0x7fff) + X, posY + Y);
  laser.flush();
  
  while (size>0) {
    posXY = pgm_read_dword(d);
    d++;
    size--;

    posX = posXY >> 16;
    posY = posXY & 0xffff;

    int tempX = posX & 0x7fff;
    if (tempX > maxXpos ) maxXpos = tempX;

    if (posX & 0x8000) {
      laser.on();
    } else {
      laser.off();
    }
    laser.sendto((posX & 0x7fff) + X, posY + Y);
  }
  laser.off();
  laser.flush();
  
  // calculate KPPS
  calcKPPS = laser.Points / (millis()-startTime);
  ms = (millis()-startTime);
}

