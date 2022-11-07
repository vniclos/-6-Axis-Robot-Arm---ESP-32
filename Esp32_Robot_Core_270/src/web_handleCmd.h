#ifndef WEB_HANDLECMD_h
#define WEB_HANDLECMD_h
#include "Arduino.h"
#include "mainDefines.h"
void handleCmd()
{
#ifdef DEBUG
    Serial.println("handleCmd ");
#endif
    fncBlinckOn();
    if (g_fnc_IsRuning == 1)
    {

        g_WebServer.send(200, "text/html", "Please wait");
        fncBlinckOff();
        return;
    }

    int iIdMotor = -9;
    String sUri = "";
    String sIdMotor = "";
    String sCmd = "";
    String szHtml = "";
    sUri = g_WebServer.uri();

    if (g_WebServer.hasArg("idMotor"))
    {
        sIdMotor = g_WebServer.arg("idMotor");
        iIdMotor = sIdMotor.toInt();
    }
    if (g_WebServer.hasArg("cmd"))
    {
        sCmd = g_WebServer.arg("cmd");
    }
#ifdef DEBUG
    Serial.print("idMotor=");
    Serial.print(iIdMotor);
    Serial.print(" cmd=");
    Serial.println(sCmd);
#endif

    if (iIdMotor == -1 && sCmd == "fnc01")
    {
        szHtml = fnc01_Servos();
    }
    if (iIdMotor == -1 && sCmd == "fnc02")
    {
        szHtml = fnc02_Servos();
    }
    if (iIdMotor > -1)
    {
        szHtml = g_Servo[iIdMotor].DoCommand(sCmd);
    }
    szHtml = "esp32 Recibido IdMotor=" + sIdMotor + " " + g_Servo[iIdMotor].getName() + " cmd=" + sCmd;
    g_WebServer.send(200, "text/html", szHtml);
    if (iIdMotor > -1)
    {
        szHtml =  g_Servo[iIdMotor].DoCommand(sCmd);
    }
    fncBlinckOff();
}
#endif