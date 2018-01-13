#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char *ssid = "****************";
const char *password = "****************";

void wifiSetup() {  

  WiFi.begin ( ssid, password );
  
  while ( WiFi.status() != WL_CONNECTED ) {
//    Serial.print (".");
    delay ( 500 );
  }

  MDNS.begin ( "laser" );

  ArduinoOTA.setHostname("laser");
  ArduinoOTA.begin();

//  Serial.print("WiFi started...");
}
