#ifndef MAINBLINCK_H
#define MAINBLINCK_H
#include "mainDefines.h"
void fncBlinckOn()
{digitalWrite(g_PinLedBlue, HIGH);
}
void fncBlinckOff()
{
    digitalWrite(g_PinLedBlue, LOW);
}
void fncBlinckSwithc()

{
    if (digitalRead(g_PinLedBlue) == HIGH)
    {
        digitalWrite(g_PinLedBlue, LOW);
    }
    else
    {
        digitalWrite(g_PinLedBlue, HIGH);
    }
}
#endif