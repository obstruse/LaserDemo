char fileName[] = __FILE__;

// Arduino IDE:
//   in the hardware subfolder of the Arduino IDE installation folder, create platform.txt:
//       compiler.cpp.extra_flags=-D__PATH__="{build.source.path}"
// Platformio IDE:
//   add to the platformio.ini this build_flag:
//       -D__PATH__=\"$PROJECT_DIR\"

char pathName[] = __PATH__;

char temp[1000];

const int objectMax = 20;
const uint32_t* objectAddress[objectMax];
const char* objectName[objectMax];
int objectSize[objectMax];
int objectCount = 0;
int objectIndex = 0;

const int genMax = 10;
void (*genAddress[genMax])(int);
const char* genName[genMax];
int genCount = 0;
int genIndex = 0;

#include "Drawing.h"
#include "Laser.h"
// Create laser instance (with laser pointer connected to digital pin 4)
Laser laser(4);

#include <TimeLib.h>

#include "wifi.h"
#include "http.h"
#include "httpWifi.h"

//--------------------------------------------
void genAlphabet(int init) {
  if (init) {
    genCount++;
    genAddress[genCount] = genAlphabet;
    genName[genCount] = "Alphabet";
  } else {
    laser.setScale(0.4);
    Drawing::drawString(String("abcdefghijklm"), 500, 3500, 1);
    Drawing::drawString(String("nopqrstuvwxyz"), 500, 1000, 1);    
  }
  laser.setScale(1);
}


//--------------------------------------------
void setup()
{ 

  Serial.begin(57600);

  // initialize object array 
  #include "ilda12k.h"
  #include "barney10.h"
  #include "horse10.h"
  #include "obama.h"
  #include "gear1.h"
  #include "gear2.h"
  #include "spiral1.h"
  #include "spiral1a.h"
  #include "spiral2.h"
  #include "spiral3.h"
    
  // initialize generator array
  genAlphabet(1);
  
  laser.init();
  laser.setScale(1);
  laser.setOffset(0,0);

  laserPoints = 0;

  wifiSetup();

  httpSetup();
  httpWifiSetup();

}

//--------------------------------------------
void loop() {

  server.handleClient();
  wifiClient();

  if (objectIndex > 0 && objectIndex <= objectCount) {
    Drawing::drawObject(objectAddress[objectIndex], objectSize[objectIndex]);
  }

  if (genIndex > 0 && genIndex <= genCount) {
    (*genAddress[genIndex])(0);
  }
    
}

