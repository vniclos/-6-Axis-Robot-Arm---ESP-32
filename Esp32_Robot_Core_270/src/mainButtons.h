#ifndef MAINBUTTONS_H
#define MAINBUTTONS_H
#include "mainDefines.h"
#ifdef DEBUG
void fncDebugButtons(int i, int pushLeft, int pushRight, int pushValidation)
{

  fncBlinckOn();
  if (g_fnc_IsRuning == 1)
  {

    fncBlinckOff();
    return;
  }
  Serial.print("fncDebugButtons i=");
  Serial.print(i);
  Serial.print("=");
  Serial.print(g_Servo[i].getName());
  Serial.print(" Pin=");
  Serial.print(g_Servo[i].getServo270().getAttachEsp32Pin());
  Serial.print(" btnLeft=");
  Serial.print(g_Servo[i].getMuxChanelButtonLeft());
  Serial.print(" btnRight=");
  Serial.print(g_Servo[i].getMuxChanelButtonRight());

  Serial.print(" pushLeft=");
  Serial.print(pushLeft);
  Serial.print(" pushRight=");
  Serial.println(pushRight);

  delay(1);
}
#endif
void fncloopServosWithButtons()
{
  if (g_fnc_IsRuning == 1)
  {
    Serial.println("fnc is running, please wait");
    return;
  }
  /*
   // DEBUG BUTTONS, uncoment this  this "for loop" for debugo id butoons, comment this for use in explotation
   for (;;)
   {
    g_counter++;
    g_Mux.loop();
   g_Mux.debugAll(g_counter);
   }
 */

  int pushLeft = 0;
  int pushRight = 0;
  int pushValidation = 0;
  int moveDegree = 0;

  for (int i = 0; i < 6; i++)
  {

    pushLeft = g_Mux.getLoopReadedChanel(g_Servo[i].getMuxChanelButtonLeft());
    pushRight = g_Mux.getLoopReadedChanel(g_Servo[i].getMuxChanelButtonRight());
    pushValidation = pushLeft + pushRight;

    if (pushValidation == 1)
    {

      if (pushLeft == 1) // mover izquierda
      {
        g_Servo[i].DoCommand("izq");
      }
      else // mover derecha
      {
        g_Servo[i].DoCommand("der");
      }
    }
    if (g_Mux.getLoopReadedChanel(11) == 1)
    {
      g_Servo[i].DoCommand("fnc01");
    }
    if (g_Mux.getLoopReadedChanel(7) == 1)
    {
      g_Servo[i].DoCommand("fhc02");
    }
    delay(1);
  }
}
void fncLoopOtherWithButtons()
{
  if (g_fnc_IsRuning == 1)
  {
    Serial.println("fnc is running, please wait");
    return;
  }
  if (g_Mux.muxDigitalRead(g_IdMuxChanelServoBtnFnc01) == 1)
  {
    g_fnc_IsRuning = 1;
    fnc01_Servos();
    g_fnc_IsRuning = 0;
  }
  if (g_Mux.muxDigitalRead(g_IdMuxChanelServoBtnFnc02) == 1)
  {
    g_fnc_IsRuning = 1;
    fnc02_Servos();
    g_fnc_IsRuning = 0;
  }
}
#endif