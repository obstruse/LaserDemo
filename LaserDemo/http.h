#ifndef HTTP_H
#define HTTP_H
#include <ESP8266WebServer.h>

ESP8266WebServer server ( 80 );
#endif

int kpps, ltd, lq;

//--------------------------------------------
//--------------------------------------------
void handleRoot() {
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;


  laser.getOptions(kpps,ltd,lq);
  
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader("Content-Type","text/html",true);
  server.send(200);

  sprintf ( temp,
  "<html>\
  <head>\
    <title>Laser</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      TD   { text-align: left; }\
    </style>\
  </head>\
  <body>\
    <h1>Laser</h1>\
    <table border=0 cellpadding=0><tr>"
  );
  server.sendContent ( temp );

//-------------------
  sprintf ( temp,
  "<td valign='top'><form><table style='float: left' border='1' cellpadding='5'>\
  <tr><th>Object</th></tr>\
  <tr><td><table border='0' cellpadding='5'>");
  server.sendContent ( temp );

  for ( int i=1; i<=objectCount; i++) {
    sprintf ( temp,
    "<tr><td><button style='width:100px' onclick='location.href=\"/select?obj=%d\"; return false;'>%s</button></td></tr>",
    i, objectName[i]);
    server.sendContent( temp );
  }

  sprintf ( temp,
  "</table></td></tr>\
  <tr><td cellpadding=10><button style='width:100px' type='submit' formaction='/select?obj=0'>Stop</button></td></tr>\
  </table></form></td>");
  server.sendContent( temp );
//-------------------

  sprintf ( temp,
  "<td valign='top'><form><table style='float: left' border='1' cellpadding='5'>\
  <tr><th>Generator</th></tr>\
  <tr><td><table border='0' cellpadding='5'>");
  server.sendContent ( temp );

  for ( int i=1; i<=genCount; i++) {
    sprintf ( temp,
    "<tr><td><button style='width:100px' onclick='location.href=\"/select?gen=%d\"; return false;'>%s</button></td></tr>",
    i, genName[i]);
    server.sendContent( temp );
  }

  sprintf ( temp,
  "</table></td></tr>\
  <tr><td cellpadding=10><button style='width:100px' type='submit' formaction='/select?gen=0'>Stop</button></td></tr>\
  </table></form></td>");
  server.sendContent( temp );
//-------------------

  sprintf ( temp,
  "<td valign='top'><form action='/serverConfig'><table style='float: left' border='1' cellpadding='5'>\
  <tr><th>Config</th></tr>\
  <tr><td cellpadding='10'>KPPS<br><input type=number style='width:100px' name='kpps' value='%d'><br>\
          LTD<br><input type=number style='width:100px' name='ltd' value='%d'><br>\
          LQ<br><input type=number style='width:100px' name='lq' value='%d'><br>\
  </td></tr>",
  kpps, ltd, lq);
  server.sendContent( temp );

  sprintf ( temp,
  "<tr><td><input type='submit' style='width:100px' value='Submit'></td></tr>\
  </table></form></td>");
  server.sendContent( temp );
//-------------------

  sprintf ( temp,
"</tr></table><br><p>Uptime: %02d:%02d:%02d</p>\
    <p>%s/%s %s %s</p>\
    </body></html>",
    hr, min % 60, sec % 60,
    pathName, fileName, __DATE__, __TIME__);
  server.sendContent ( temp );

  server.sendContent (" ");

}

//--------------------------------------------
void objectSelect() {
  String inObj;

  inObj = server.arg("obj");
  objectIndex = inObj.toInt();

  inObj = server.arg("gen");
  genIndex = inObj.toInt();
  
  // 204: No Content
  //      The server successfully processed the request and is not returning any content
  server.send ( 204, "text/plain", "");

}

//--------------------------------------------
void serverConfig() {
  String inObj;

  inObj = server.arg("kpps");
  kpps = inObj.toInt();

  inObj = server.arg("ltd");
  ltd = inObj.toInt();
  
  inObj = server.arg("lq");
  lq = inObj.toInt();

  laser.setOptions(kpps, ltd, lq);
  
  // 204: No Content
  //      The server successfully processed the request and is not returning any content
  server.send ( 204, "text/plain", "");

}

//--------------------------------------------
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

//--------------------------------------------
//--------------------------------------------
void httpSetup() {

  server.on ( "/", handleRoot );
  server.on ( "/select", objectSelect );
  server.on ( "/serverConfig", serverConfig );
  server.onNotFound ( handleNotFound );
  server.begin();

//  Serial.println("http started");
}

