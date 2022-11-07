#ifndef MYSETUP_H
#define MYSETUP_H
#include <Arduino.h>
#include <Esp32servo270.h>
#include "ClsServo.h"
#include "ClsCD74HC4067.h"
#include "mainDefines.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>

#include "web_handle.h"
#include "web_handleCmd.h"
void fncSetupServos()
{

  for (int i = 0; i < 6; i++)
  {
    // g_ServoCfgAttachMoveMin[i] = map(g_ServoCfgAttachMoveMin[i], 0, g_ServoCfgAttachDatasheetDegreeMax[i], g_ServoCfgAttachDatasheetUsMin[i], g_ServoCfgAttachDatasheetUsMax[i]);
    // g_ServoCfgAttachMoveMax[i] = map(g_ServoCfgAttachMoveMax[i], 0, g_ServoCfgAttachDatasheetDegreeMax[i], g_ServoCfgAttachDatasheetUsMin[i], g_ServoCfgAttachDatasheetUsMax[i]);
    // g_ServoCfgAttachMoveUsIni[i] = map(g_ServoCfgAttachMoveIni[i], 0, g_ServoCfgAttachDatasheetDegreeMax[i], g_ServoCfgAttachDatasheetUsMin[i], g_ServoCfgAttachDatasheetUsMax[i]);
    #ifdef DEBUG
    Serial.println("-----------");
    Serial.print("Min map: ");
    Serial.print(g_ServoCfgAttachMoveMin[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetDegreeMax[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMin[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMax[i]);
    Serial.print(" -> ");
    Serial.println(g_ServoCfgAttachMoveMin[i]);

    Serial.print("Max map: ");
    Serial.print(g_ServoCfgAttachMoveMax[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetDegreeMax[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMin[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMax[i]);
    Serial.print(" -> ");
    Serial.println(g_ServoCfgAttachMoveMax[i]);
    Serial.print("Ini map: ");
    Serial.print(g_ServoCfgAttachMoveIni[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetDegreeMax[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMin[i]);
    Serial.print(" - ");
    Serial.print(g_ServoCfgAttachDatasheetUsMax[i]);
    Serial.print(" -> ");
    Serial.println(g_ServoCfgAttachMoveIni[i]);
#endif
    g_Servo[i].Setup(
        i,
        g_ServoCfgName[i],
        g_ServoCfgModel[i],
        g_IdMuxChanelServoBtnLeft[i],
        g_IdMuxChanelServoBtnRight[i],
        g_PinsServo[i],
        g_ServoCfgAttachDatasheetUsMin[i],
        g_ServoCfgAttachDatasheetUsMax[i],
        g_ServoCfgAttachDatasheetDegreeMax[i],
        g_ServoCfgAttachMoveMin[i],
        g_ServoCfgAttachMoveMax[i],
        g_ServoCfgAttachMoveIni[i],
        g_ServoCfgAttachMoveUsSteep[i]); // longitud del paso en microsegundos
  }
}
void fncSetupMultiCoreTask()
{

  xTaskCreatePinnedToCore(
      Loop_Core_0,     /* Task function. */
      "Core_0_Task_1", /* name of task. */
      10000,           /* Stack size of task */
      NULL,            /* parameter of the task */
      1,               /* priority of the task */
      &Core_0_Task_1,  /* Task handle to keep track of created task */
      0);              /* pin task to core 0 */

  xTaskCreatePinnedToCore(
      Loop_Core_1,     /* Task function. */
      "Core_1_Task_2", /* name of task. */
      10000,           /* Stack size of task */
      NULL,            /* parameter of the task */
      1,               /* priority of the task */
      &Core_1_Task_2,  /* Task handle to keep track of created task */
      1);              /* pin task to core 1 */
  Serial.println("fncSetupMultiCoreTask");
}
void fncSetupMux()
{
  g_Mux.setup(g_PinsMuxS0_4[0], g_PinsMuxS0_4[1], g_PinsMuxS0_4[2], g_PinsMuxS0_4[3], g_PinsMuxSig, g_PinsMuxSEn);
  // g_Mux.setup(g_PinsMuxS0_4[0], g_PinsMuxS0_4[1], g_PinsMuxS0_4[2], g_PinsMuxS0_4[3], g_PinsMuxSig, g_PinsMuxSEn);
}

void fncSetupWifi()
{

  Serial.println();

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(g_WifiIpLocalP, g_WifiIpGateway, g_WifiIpMask) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.print(g_WifiSsid);
  Serial.print(" - ");
    Serial.println(g_WifiPwd);
  Serial.print(" - ");
  Serial.print(WiFi.softAP(g_WifiSsid, g_WifiPwd) ? "Ready" : "Failed!");
  // WiFi.softAP(ssid);
  // WiFi.softAP(ssid, passphrase, channel, ssdi_hidden, max_connection)

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  if (MDNS.begin(g_WifiSsid))
  {
    Serial.println("MDNS robot responder started");
  }

}

void fncSetupWebserver()
{
  Serial.println("fnc_Web_Setup in");
  // g_WebServer.on("/fncStatusGet", handleSTATUSGET);
  g_WebServer.on("/", handleROOT);
  g_WebServer.on("/js.js", handleJS);
  g_WebServer.on("/css.css", handleCSS);
  g_WebServer.on("/svg.svg", handleSVG);

  // g_WebServer.on("/fncDebug", handleDEBUG);
  g_WebServer.on("/cmd", handleCmd); // for one relay /fncAutomatic?id=n
  g_WebServer.onNotFound(handleNotFound);
  g_WebServer.begin();
  Serial.println("fnc_Web_Setup out");
}

#endif