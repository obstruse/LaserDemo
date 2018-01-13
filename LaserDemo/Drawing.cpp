// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de
#include "Drawing.h"
//#include "Font2.h"
#include "font_nv202.h"



void Drawing::drawString(String text, int x, int y, int count)
{
  for (int loop = 0; loop < count; loop ++)
  {
    int i = 0;
    int x1 = x;
    while (text.charAt(i) != '\0')
    {
       x1 += drawLetter(text.charAt(i), x1, y); 
       i ++;
    }
  }
}

long Drawing::stringAdvance(String text)
{
  long adv = 0;
  int i = 0;
  while (text.charAt(i) != '\0')
  {
     adv += advance(text.charAt(i)); 
     i ++;
  }
  return adv;
}

long Drawing::advance(byte letter)
{
  long adv = 850;
  if (letter == 'I') {
    adv = 200;
  } else
  if (letter == 'W') {
//    adv = 1000;
    adv = 800;
  }
  return adv;
}

int minXpos;
int maxXpos;

long Drawing::drawLetter(byte letter, long translateX, long translateY)
{
  long adv = advance(letter);

//  minXpos = 4096;
  maxXpos = 0;

  // Serial.println("drawletter");
  switch (letter)
  {
    case 'A': drawObject(font_32, sizeof(font_32)/4, translateX, translateY); break;
    case 'B': drawObject(font_33, sizeof(font_33)/4, translateX, translateY); break;
    case 'C': drawObject(font_34, sizeof(font_34)/4, translateX, translateY); break;
    case 'D': drawObject(font_35, sizeof(font_35)/4, translateX, translateY); break;
    case 'E': drawObject(font_36, sizeof(font_36)/4, translateX, translateY); break;
    case 'F': drawObject(font_37, sizeof(font_37)/4, translateX, translateY); break;
    case 'G': drawObject(font_38, sizeof(font_38)/4, translateX, translateY); break;
    case 'H': drawObject(font_39, sizeof(font_39)/4, translateX, translateY); break;
    case 'I': drawObject(font_40, sizeof(font_40)/4, translateX, translateY); break;
    case 'J': drawObject(font_41, sizeof(font_41)/4, translateX, translateY); break;
    case 'K': drawObject(font_42, sizeof(font_42)/4, translateX, translateY); break;
    case 'L': drawObject(font_43, sizeof(font_43)/4, translateX, translateY); break;
    case 'M': drawObject(font_44, sizeof(font_44)/4, translateX, translateY); break;
    case 'N': drawObject(font_45, sizeof(font_45)/4, translateX, translateY); break;
    case 'O': drawObject(font_46, sizeof(font_46)/4, translateX, translateY); break;
    case 'P': drawObject(font_47, sizeof(font_47)/4, translateX, translateY); break;
    case 'Q': drawObject(font_48, sizeof(font_48)/4, translateX, translateY); break;
    case 'R': drawObject(font_49, sizeof(font_49)/4, translateX, translateY); break;
    case 'S': drawObject(font_50, sizeof(font_50)/4, translateX, translateY); break;
    case 'T': drawObject(font_51, sizeof(font_51)/4, translateX, translateY); break;
    case 'U': drawObject(font_52, sizeof(font_52)/4, translateX, translateY); break;
    case 'V': drawObject(font_53, sizeof(font_53)/4, translateX, translateY); break;
    case 'W': drawObject(font_54, sizeof(font_54)/4, translateX, translateY); break;
    case 'X': drawObject(font_55, sizeof(font_55)/4, translateX, translateY); break;
    case 'Y': drawObject(font_56, sizeof(font_56)/4, translateX, translateY); break;
    case 'Z': drawObject(font_57, sizeof(font_57)/4, translateX, translateY); break;
    
    case 'a': drawObject(font_64, sizeof(font_64)/4, translateX, translateY); break;
    case 'b': drawObject(font_65, sizeof(font_65)/4, translateX, translateY); break;
    case 'c': drawObject(font_66, sizeof(font_66)/4, translateX, translateY); break;
    case 'd': drawObject(font_67, sizeof(font_67)/4, translateX, translateY); break;
    case 'e': drawObject(font_68, sizeof(font_68)/4, translateX, translateY); break;
    case 'f': drawObject(font_69, sizeof(font_69)/4, translateX, translateY); break;
    case 'g': drawObject(font_70, sizeof(font_70)/4, translateX, translateY); break;
    case 'h': drawObject(font_71, sizeof(font_71)/4, translateX, translateY); break;
    case 'i': drawObject(font_72, sizeof(font_72)/4, translateX, translateY); break;
    case 'j': drawObject(font_73, sizeof(font_73)/4, translateX, translateY); break;
    case 'k': drawObject(font_74, sizeof(font_74)/4, translateX, translateY); break;
    case 'l': drawObject(font_75, sizeof(font_75)/4, translateX, translateY); break;
    case 'm': drawObject(font_76, sizeof(font_76)/4, translateX, translateY); break;
    case 'n': drawObject(font_77, sizeof(font_77)/4, translateX, translateY); break;
    case 'o': drawObject(font_78, sizeof(font_78)/4, translateX, translateY); break;
    case 'p': drawObject(font_79, sizeof(font_79)/4, translateX, translateY); break;
    case 'q': drawObject(font_80, sizeof(font_80)/4, translateX, translateY); break;
    case 'r': drawObject(font_81, sizeof(font_81)/4, translateX, translateY); break;
    case 's': drawObject(font_82, sizeof(font_82)/4, translateX, translateY); break;
    case 't': drawObject(font_83, sizeof(font_83)/4, translateX, translateY); break;
    case 'u': drawObject(font_84, sizeof(font_84)/4, translateX, translateY); break;
    case 'v': drawObject(font_85, sizeof(font_85)/4, translateX, translateY); break;
    case 'w': drawObject(font_86, sizeof(font_86)/4, translateX, translateY); break;
    case 'x': drawObject(font_87, sizeof(font_87)/4, translateX, translateY); break;
    case 'y': drawObject(font_88, sizeof(font_88)/4, translateX, translateY); break;
    case 'z': drawObject(font_89, sizeof(font_89)/4, translateX, translateY); break;
    
    case '0': drawObject(font_15, sizeof(font_15)/4, translateX, translateY); break;
    case '1': drawObject(font_16, sizeof(font_16)/4, translateX, translateY); break;
    case '2': drawObject(font_17, sizeof(font_17)/4, translateX, translateY); break;
    case '3': drawObject(font_18, sizeof(font_18)/4, translateX, translateY); break;
    case '4': drawObject(font_19, sizeof(font_19)/4, translateX, translateY); break;
    case '5': drawObject(font_20, sizeof(font_20)/4, translateX, translateY); break;
    case '6': drawObject(font_21, sizeof(font_21)/4, translateX, translateY); break;
    case '7': drawObject(font_22, sizeof(font_22)/4, translateX, translateY); break;
    case '8': drawObject(font_23, sizeof(font_23)/4, translateX, translateY); break;
    case '9': drawObject(font_24, sizeof(font_24)/4, translateX, translateY); break;
    case '!': drawObject(font_0,  sizeof(font_0)/4,  translateX, translateY); break;
    case '?': drawObject(font_30, sizeof(font_30)/4, translateX, translateY); break;
    case '.': drawObject(font_13, sizeof(font_13)/4, translateX, translateY); break;
    case ' ':    
        break;

  }
  // Serial.println("drawletter out");
  // minXpos should always be zero
  adv = maxXpos + 200;
//  Serial.print ("adv "); Serial.print(letter); Serial.print(" "); Serial.println (adv);
  return adv;
}

void Drawing::drawObject(const uint32_t* data, int size, long translateX, long translateY)
{
  // Serial.println("drawobject");
  const uint32_t* d = data;
  unsigned int posX;
  unsigned int posY;
  unsigned int posXY;

  // sendToDAC() - direct to galvos
  // sendtoRaw() - provides Laser Quality steps
  // sendto()    - scaling + clipping + Laser Quality

  // give the mirrors time to get to the first position...before turning on laser
  posXY = pgm_read_dword(d);
  posX = posXY >> 16;
  posY = posXY & 0xffff;
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);

  while (size>0) {
    posXY = pgm_read_dword(d);
    d++;
    size--;

    posX = posXY >> 16;
    posY = posXY & 0xffff;

    int tempX = posX & 0x7fff;
    if (tempX > maxXpos ) maxXpos = tempX;
//minXpos should always be zero
//    if (tempX < minXpos ) minXpos = tempX;

    if (posX & 0x8000) {
      laser.on();
    } else {
      laser.off();
    }
    laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  }
  laser.off();
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);
  laser.sendto((posX & 0x7fff) + translateX, posY + translateY);

}

long SIN(unsigned int angle);
long COS(unsigned int angle);

void Drawing::drawObjectRotated(const unsigned short* data, int size, long centerX, long centerY, int angle)
{
  const unsigned short* d = data;
  unsigned short posX;
  unsigned short posY;
  while (size>0) {
    posX = pgm_read_dword_far(d);
//    posX = d[0];
    d++;
    posY = pgm_read_dword_far(d);
//    posY = d[0];
    d++;
    size--;

    if (posX & 0x8000) {
      laser.on();
    } else {
      laser.off();
    }
    FIXPT x = (long)(posX & 0x7fff) - centerX;
    FIXPT y = ((long)posY) - centerY;
    FIXPT x1 = COS(angle) * x - SIN(angle) * y;
    FIXPT y1 = COS(angle) * y + SIN(angle) * x;
    laser.sendto(TO_INT(x1), TO_INT(y1));
  }
  laser.off();
}

/*
void Drawing::drawObjectRotated3D(const unsigned short* data, int size, long centerX, long centerY, int angleX, int angleY, int zDist)
{
  Matrix3 world;
  Matrix3 tmp;
  tmp = Matrix3::rotateX(angleX);
  Matrix3::multiply(Matrix3::rotateY(angleY), tmp, world);
  
  laser.setEnable3D(true);
  laser.setMatrix(world);
  drawObject(data,size, -centerX, -centerY);  
  laser.setEnable3D(false);
}
*/

void Drawing::calcObjectBox(const unsigned short* data, int size, long& centerX, long& centerY, long& width, long& height)
{
  const unsigned short* d = data;
  unsigned short posX;
  unsigned short posY;
  unsigned short x0 = 4096;
  unsigned short y0 = 4096;
  unsigned short x1 = 0;
  unsigned short y1 = 0;
  while (size>0) {
//    posX = pgm_read_dword(d) & 0x7fff;
      posX = d[0] & 0x7fff;
    d++;
//    posY = pgm_read_dword(d);
      posY = d[0];
    d++;
    size--;
    if (posX < x0) x0 = posX;
    if (posY < y0) y0 = posY;
    if (posX > x1) x1 = posX;
    if (posY > y1) y1 = posY;
  }
  centerX = (x0 + x1) / 2;
  centerY = (y0 + y1) / 2;
  width = x1 - x0;
  height = y1 - y0;
}

