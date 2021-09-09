#ifndef HTTP_H
#define HTTP_H
#include <ESP8266WebServer.h>

ESP8266WebServer server ( 80 );
#endif

// second page of http code

//--------------------------------------------
void handleConfig() {

  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader("Content-Type", "text/html", true);
  server.sendHeader("Cache-Control", "no-cache");
  server.send(200);

  /*-------------------------------------------*/
  sprintf ( temp,
            "<html>\
<head><title>WIFI Config</title></head>\
<style> body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; } </style>\
<body>\
<h1>WIFI Config</h1>" );
  server.sendContent ( temp );

  /*-------------------------------------------*/
  sprintf ( temp,
            "<form action='/httpReconnect'>\
<table border=1 cellpadding=5>\
<tr><td><input type='submit' name='status' value='Reconnect STA'></td></tr>\
</table>\
</form>");
  server.sendContent ( temp );

  /*-------------------------------------------*/
  sprintf ( temp,
            "<form action='/httpAP'>\
<table border=1 cellpadding=5>\
<tr><td><input type='submit' name='status' value='Connect AP'></td></tr>\
</table>\
</form>");
  server.sendContent ( temp );

  //--------------------------------------------
  sprintf ( temp,
            "<table border=1 cellpadding=5>\
<tr><th colspan=2>STA</th></tr>\
<form action='/httpSTA'>\
<tr><th>SSID</th><td><input type='text' name='staSSID' placeholder='SSID'></td></tr>\
<tr><th>PW</th>  <td><input type='text' name='staPW'   placeholder='PW'  ></td></tr>\
<tr><td colspan=2><center><input type='submit' name='STA' value='Connect'></center></form></td></tr> \
</table><br>"
          );
  server.sendContent ( temp );

  //--------------------------------------------
  sprintf ( temp,
            "<table border=1 cellpadding=5>\
<tr><th colspan=2>IP</th></tr>\
<tr><th>STA</th><td>%s</td></tr>\
<tr><th>AP</th><td>%s</td></tr>\
</table><br>",
            WiFi.localIP().toString().c_str(),
            WiFi.softAPIP().toString().c_str()
          );
  server.sendContent ( temp );

  //--------------------------------------------
  sprintf ( temp,
            "<form action='/scan'>\
<table border=1 cellpadding=5>\
<tr><td colspan=2><center><input type='submit' name='status' value='Scan'></center></td></tr>\
<tr><th>SSID</th><th>RSSI</th></tr>");
  server.sendContent ( temp );

  for (int i = 0; i < WIFI.aps; i++ ) {
    sprintf ( temp,
    "<tr><td>%s</td><td>%d</td></tr>",
    WiFi.SSID(i).c_str(), WiFi.RSSI(i) );
    server.sendContent ( temp );
  }
  
  sprintf ( temp,
  "</table></form>");
  server.sendContent ( temp );

  /*-------------------------------------------*/
  sprintf ( temp, "  </body></html>" );
  server.sendContent ( temp );

  server.sendContent ("");
}

//--------------------------------------------
void httpSTA() {

  WIFI.ssid = server.arg("staSSID");
  WIFI.psk  = server.arg("staPW");

  wifiSTA();
  
  server.sendHeader("Location", String("/config"), true);
  server.send ( 302, "text/plain", "");

}

//--------------------------------------------
void httpReconnect() {

  wifiReconnect();
  
  server.sendHeader("Location", String("/config"), true);
  server.send ( 302, "text/plain", "");

}

//--------------------------------------------
void httpAP() {

  wifiAP();
 
  server.sendHeader("Location", String("/config"), true);
  server.send ( 302, "text/plain", "");

}

//--------------------------------------------
void httpScan() {

  wifiScan();

  delay(1000);  // give it some time to execute...
  
  // 204: No Content
  //      The server successfully processed the request and is not returning any content
  //server.send ( 204, "text/plain", "");

  // refresh root
  server.sendHeader("Location", String("/config"), true);
  server.send ( 302, "text/plain", "");

}

//--------------------------------------------
void httpWifiSetup() {

  // will they work AFTER the first server.begin? (might make it easy to add includes with http functionality
  server.on ( "/config", handleConfig );
  server.on ( "/httpReconnect", httpReconnect );
  server.on ( "/httpAP", httpAP );
  server.on ( "/httpSTA", httpSTA );
  server.on ( "/scan", httpScan );

  server.begin();
}
