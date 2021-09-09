char fileName[] = __FILE__;

char temp[1000];

const uint32_t* objectAddress[20];
const char* objectName[20];
int objectSize[20];
int objectCount = 0;
int objectIndex = 0;

void (*genAddress[10])(int);
const char* genName[10];
int genCount = 0;
int genIndex = 0;

#include "wifi.h"

#include "Drawing.h"
#include "Laser.h"

#include <TimeLib.h>

// Create laser instance (with laser pointer connected to digital pin 4)
Laser laser(4);

#include "http.h"
#include "httpWifi.h"

int objectNumber = 0;
int objectStart = 0;
int objectTime = 0;
int objectCalls = 0;


// objects
#include "horse10.h"
#include "barney10.h"
#include "ilda12k.h"
#include "gear1.h"
#include "gear2.h"
#include "spiral1.h"
#include "spiral1a.h"
#include "spiral2.h"
#include "spiral2a.h"
#include "spiral3.h"
#include "obama.h"


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
  barney10();
  gear1();
  gear2();
  horse10();
  ilda12k();
  obama();
  spiral1();
  spiral1a();
  spiral2();
  spiral2a();
  spiral3();
    
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

