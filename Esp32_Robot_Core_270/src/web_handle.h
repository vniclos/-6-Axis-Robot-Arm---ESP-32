#ifndef _WEB_HANDLE_H
#define _WEB_HANDLE_H
#include "mainDefines.h"
#include "web_root.h"
#include "web_js.h"
#include "web_css.h"
#include "web_svg.h"

#define PIN_LEDINTBLUE2 2
//=================================================
//=================================================
//=================================================
void fncDebugArgs()
{
  String sz = "Args: ";
  ;
  sz += g_WebServer.args() + "\n";
  for (int i = 0; i < g_WebServer.args(); i++)
  {

    sz += "Arg nº" + (String)i + "–> ";
    sz += g_WebServer.argName(i) + ": ";
    sz += g_WebServer.arg(i) + "\n";
  }

  // Serial.println(sz);
}
//=================================================
// void handleROOT()
//=================================================
void handleROOT()
{
#ifdef DEBUG
  Serial.println("handleROOT");
#endif
  // Serial.println("handleRoot");
  fncBlinckOn();

  g_WebServer.send(200, "text/html", g_HTML_Web_root);
  fncBlinckOff();
}

void handleJS()
{
  #ifdef DEBUG
  Serial.println("handleJS");
  #endif
  digitalWrite(g_PinLedBlue, 1);
  g_WebServer.send(200, "application/javascript", g_HTML_Web_JS);
  digitalWrite(g_PinLedBlue, 0);
}
//==============================================
void handleCSS()
{
  #ifdef DEBUG
  Serial.println("handleCSS");
  #endif
  digitalWrite(g_PinLedBlue, 1);
  g_WebServer.send(200, "text/css", g_HTML_Web_CSS);
  digitalWrite(g_PinLedBlue, 0);
}
void handleSVG()
{
  #ifdef DEBUG
  Serial.println("handleSVG");
  #endif
   fncBlinckOn();
  g_WebServer.send(200, "image/svg+xml", g_HTML_Web_SVG);
    fncBlinckOff();
}
//=================================================
//=================================================
void handleNotFound()
{
  fncBlinckOn();
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += g_WebServer.uri();
  message += "\nMethod: ";
  message += (g_WebServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += g_WebServer.args();
  message += "\n";

  for (uint8_t i = 0; i < g_WebServer.args(); i++)
  {
    message += " " + g_WebServer.argName(i) + ": " + g_WebServer.arg(i) + "\n";
  }

  g_WebServer.send(404, "text/plain", message);
   fncBlinckOff();
}

#endif