#include <Arduino.h>
#include <Esp32servo270.h>

#include "ClsServo.h"
#include "ClsCD74HC4067.h"
#include "mainDefines.h"
#include "mainBlinCk.h"
#include "mainSetup.h"
#include "mainServos"
#include "mainButtons.h"

void setup()
{
  pinMode(g_PinLedBlue, OUTPUT);
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Starting setup");
#endif
  fncSetupMux();
  fncSetupServos();
  fncSetupWifi();
  fncSetupWebserver();
  fncSetupMultiCoreTask();
  fnc01_Servos();
  Serial.println("End setup");
}

//---------------------------------------------------------

// Loop_Core_0: blinks an LED every 1000 ms
void Loop_Core_0(void *pvParameters)
{
#ifdef DEBUG
  Serial.println("");
  Serial.print("Core_0_Task_1 running on core ");

  Serial.println(xPortGetCoreID());
  Serial.println("");
#endif
  for (;;)
  {
    g_Mux.loop(); // read all chanels
    fncloopServosWithButtons();
    fncLoopOtherWithButtons();
  }
}

// Loop_Core_1: blinks an LED every 700 ms
void Loop_Core_1(void *pvParameters)
{
#ifdef DEBUG
  Serial.println("");
  Serial.print("Core_1_Task_2 running on core ");
  Serial.println(xPortGetCoreID());
#endif
  for (;;)
  {

    //digitalWrite(g_PinLedBlue, LOW);
    g_WebServer.handleClient();
    //  delay(1);
  }
}

void loop()
{
  // loop is split into two separate tasks, each running that assigned to a different core
  // the tasks start  calling function   fncSetupMultiCoreTask() from setup() function
  // ----------   -------------------------------------   --------------------------
  //  Core        loop function                            main fun
  // ----------   -------------------------------------   --------------------------
  // Core 1    -> Loop_Core_1( void * pvParameters )   -> g_WebServer.handleClient()
  // core 0    -> Loop_Core_0 ( void * pvParameters )  -> call fncloopServosWithButtons
}
