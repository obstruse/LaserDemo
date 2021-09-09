#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>

struct {
  String ssid   = "";
  String psk    = "";
  boolean dns = false;
  boolean ota = false;
  int aps = 0;
  String staMessage = "";
} WIFI;

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;

/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);

char IOTname[64];

//--------------------------------------------
void wifiScanResult(int networksFound) {
  WIFI.aps = networksFound;
}

//--------------------------------------------
void wifiScan() {
  WIFI.aps = 0;
  WiFi.scanNetworksAsync(wifiScanResult);
}

//--------------------------------------------
void wifiAP() {

  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP( IOTname, "carbondioxide");

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  WIFI.dns  = true;

  Serial.printf("AP started: %s (192.168.4.1)\n", IOTname);

}

//--------------------------------------------
void wifiSTA() {
  // adding a new STA

  WiFi.mode(WIFI_AP_STA);

  Serial.printf(" SSID: %s PSK: %s X\n", WIFI.ssid.c_str(), WIFI.psk.c_str());

  WiFi.persistent(true);
  WiFi.begin( WIFI.ssid, WIFI.psk );
  WiFi.persistent(false);

  WiFi.waitForConnectResult();

}

//--------------------------------------------
void wifiReconnect() {
  // reconnecting to a previous STA

  WiFi.mode(WIFI_AP_STA);
  WiFi.reconnect();
  WiFi.waitForConnectResult();

  // it should do the MDNS and Time stuff too...?
  // maybe not. if boot STA, add AP, then reconnect, don't need to...
  //            if boot AP, then reconnect STA, need, but eh, not likely.
  // I guess I'll just leave it that MDNS/time only started when boot STA

}

//--------------------------------------------
void wifiClient() {
  if ( WIFI.ota && ( WiFi.status() == WL_CONNECTED ) ) {
    ArduinoOTA.handle();
  }

  if ( WIFI.dns ) {
    dnsServer.processNextRequest();
  }
}

//--------------------------------------------
void wifiSetup() {

  Serial.println(" ");
  strncpy(IOTname, strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName, sizeof(IOTname) - 1);
  IOTname[ strcspn(IOTname, ".") ] = '\0';
  Serial.printf("IOTname: %s\n", IOTname);

  // WIFI setup
  WiFi.persistent(false); // don't write the WIFI setting changes to EEPROM
  WiFi.setAutoConnect(false);
  WiFi.setAutoReconnect(true);    // turns out that 'true' works a lot better, and 'false' doens't really improve response much
  WiFi.mode(WIFI_STA);

  WiFi.begin ();    // use last ssid/password

  if ( WiFi.waitForConnectResult() == WL_CONNECTED ) {

    MDNS.begin ( IOTname );
    MDNS.addService("http", "tcp", 80);

    ArduinoOTA.setHostname( IOTname );
    ArduinoOTA.begin();
    WIFI.ota = true;

    Serial.println(" ");

  } else {
    Serial.printf ("Unable to connect, setting up Access Point: %s (192.168.4.1\n", IOTname);

    wifiAP();
    wifiScan();

  }

  Serial.println("WiFi started");
}