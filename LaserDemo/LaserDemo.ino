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

struct {
  int points = 0;
  int * x;
  int * y;
} DRAW;

#include "Drawing.h"
#include "Laser.h"
// Create laser instance (with laser pointer connected to digital pin 4)
Laser laser(4);

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
void genSquare(int init) {
  int kpps, ltd, lq, lq2;

  if (init) {
    genCount++;
    genAddress[genCount] = genSquare;
    genName[genCount] = "Square";
  } else {

    laser.getOptions(kpps,ltd,lq);
    laser.setOptions(kpps,ltd,75);

    laser.on();

    laser.sendto(0,0);
    laser.sendto(0,4095);
    laser.sendto(4095,4095);
    laser.sendto(4095,0);
    laser.sendto(0,0);
  
    laser.off();
    laser.flush();

    laser.getOptions(kpps,ltd,lq2);
    laser.setOptions(kpps,ltd,lq);
  }

}

//--------------------------------------------
void drawPoints(int init) {

  if (init) {
    genCount++;
    genAddress[genCount] = drawPoints;
    genName[genCount] = "Draw";
  } else {
    if ( DRAW.points ) {                  // if there are points to draw...
      laser.sendto(DRAW.x[0], DRAW.y[0]); // ...send the first point...
      laser.on();                         // ... and then turn the laser on. (doesn't increment queue)
      laser.flush();                      // increments the queue a few times so single point draw will be visible
      for ( int i = 1; i < DRAW.points; i++) {
        laser.sendto(DRAW.x[i], DRAW.y[i]);
      }
    }
    laser.off();                          // the Off is enqued... (doesn't increment queue)
    laser.flush();                        // flush the queue so that the off is executed
  }
}

//--------------------------------------------
void setup()
{ 

  Serial.begin(57600);

  // initialize object array 
  #include "ilda12k.h"
  #include "cat20.h"
  #include "dylan5k.h"
  #include "petermax2.h"
  #include "barney10.h"
  #include "horse10.h"
  #include "gear1.h"
  #include "gear2.h"
  #include "spiral1.h"
  #include "spiral1a.h"
  #include "spiral2.h"
  #include "spiral3.h"
    
  // initialize generator array
  genAlphabet(1);
  genSquare(1);
  drawPoints(1);

  laser.init();
  laser.setScale(1);
  laser.setOffset(0,0);

  laserPoints = 0;

  wifiSetup();

  httpSetup();
  httpWifiSetup();

  // shutter pin
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW); 

}

//--------------------------------------------
void loop() {

  server.handleClient();
  wifiClient();

  extern unsigned long nextYield;
  nextYield = millis() + 1000;    // feed the dog at least every 1000 milliseconds

  if (objectIndex > 0 && objectIndex <= objectCount) {
    // modifications for cat capture, using remote shutter, not using script
    //laser.sendto(0,0);
    //
    //digitalWrite(12, HIGH);   // trigger camera, focus locked
    //delay(100);               
    //digitalWrite(12, LOW);    // ...begin exposure
    //delay(600);               // wait a bit for exposure to start

    Drawing::drawObject(objectAddress[objectIndex], objectSize[objectIndex]);

    // modifications for cat capture
    //laser.sendto(4095,4095);
    //objectIndex = 0;
  }

  if (genIndex > 0 && genIndex <= genCount) {
    (*genAddress[genIndex])(0);
  }
    
}

