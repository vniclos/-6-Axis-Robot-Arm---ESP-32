#ifndef MAINDEFINES_H
#define MAINDEFINES_H
#include <Arduino.h>
#include <WebServer.h>
#include "ClsServo.h"
#include "ClsCD74HC4067.h"
#define DEBUG
//#define WTD_INTERVAL 4000000

TaskHandle_t Core_0_Task_1;
TaskHandle_t Core_1_Task_2;
void Loop_Core_1(void *pvParameters);
void Loop_Core_0(void *pvParameters);

const int g_PinLedBlue = 2;

const int g_PinsMuxSEn = 25;                  // gris no uso
const int g_PinsMuxSig = 13;                  // naranja
const int g_PinsMuxS0_4[] = {26, 27, 14, 12}; // Amarillo,verde,azul, marron
uint32_t g_MuxCounter = 0;

// library esp32_servo Recommend only the following pins 2,4,12-19,21-23,25-27,32-33
// const int g_PinsServo[6] ={15,2,4,5,18,19};
const int g_ServoCount = 6;
const int g_ServoDS3225MG_UsMin = 500;  //µseg
const int g_ServoDS3225MG_UsMax = 2500; //µseg
const int g_ServoDS3225MG_DgMax = 270;  // degree

const int g_ServoMG996R_UsMin = 500;  //µseg
const int g_ServoMG996R_UsMax = 2000; //µseg
const int g_ServoMG996R_DgMax = 180;  // degree

const int g_PinsId[6] = {0, 1, 2, 3, 4, 5};
const int g_PinsServo[6] = {21, 4, 19, 32, 23, 33};
const String g_ServoCfgName[6] = {
    "Pinza",
    "M. Giro",
    "M. Vertical",
    "Brazo 2",
    "Brazo 1",
    "Base",
};
const String g_ServoCfgModel[6] = {"MG996R", "MG996R", "MG996R", "DS3225MG", "DS3225MG", "MG996R"};
const int g_ServoCfgAttachMoveMin[6] = {600, 1200, 700, 950, 1120, 600};
const int g_ServoCfgAttachMoveIni[6] = {800, 1500, 1180, 1150, 1400, 1270}; // 1267
const int g_ServoCfgAttachMoveMax[6] = {1160, 1800, 2000, 1560, 1550, 1472};

//int g_moves_01[7][2] = {{0, 600}, {3, 1563}, {2, 1798}, {4, 1368}, {0, 1035}, {4, 1500}, {3, 1171}};              // tomar pieza
int g_moves_01[7][2] =   {{0, 600}, {3, 1520},  {2, 1798}, {4, 1363}, {0, 1035}, {4, 1500}, {3, 1171}};              // tomar pieza
int g_moves_02_0[8][2] = {{5, 1450}, {2, 1048}, {3, 1410}, {4, 1130}, {1, 1639}, {0, 663},  {2, 1000}, {4, 1270}}; // dejar pieza en 0
int g_moves_02_1[8][2] = {{5, 1295}, {2, 1464}, {3, 1280}, {4, 1189}, {1, 1639}, {0, 663}, {2, 1000}, {4, 1270}}; // dejar pieza en 1

int g_moves_02_2[8][2] = {{5, 1103}, {2, 1066}, {3, 1377}, {4, 1123}, {1, 1374}, {0, 663}, {2, 1000}, {4, 1270}}; // dejar pieza en 2
int g_moves_02_3[8][2] = {{5, 1149}, {2, 1320}, {3, 1551}, {4, 1285}, {1, 1382}, {0, 663}, {2, 1200}, {4, 1270}}; // dejar piezaen 3
int g_moves_02_4[8][2] = {{5, 1377}, {2, 1510}, {3, 1347}, {4, 1225}, {1, 1255}, {0, 663}, {2, 1200}, {4, 1270}}; // dejar piezaen 4

// 0.5 a 1 milisegundo para la posición 0° y 2 a 2.4 milisegundos para la posición de 180°
// DS3225MG  270 ° (cuando 500 ~ 2500 µseg) 3) Posición neutra: 1500µsec
// TODO AJUSTAR MIN STEEP
const int g_ServoSteepUs_Default = 8;
const int g_ServoSteepUs_Fast = 18;
const int g_ServoSteepUs_Slowly = 3;
// TODO AJUSTAR MIN MAX values from datasheet
const int g_ServoCfgAttachDatasheetUsMin[g_ServoCount] = {g_ServoMG996R_UsMin, g_ServoMG996R_UsMin, g_ServoMG996R_UsMin, g_ServoDS3225MG_UsMin, g_ServoDS3225MG_UsMin, g_ServoMG996R_UsMin};     // callibration: 0<> ->Change  default value on setup
const int g_ServoCfgAttachDatasheetUsMax[g_ServoCount] = {g_ServoMG996R_UsMax, g_ServoMG996R_UsMax, g_ServoMG996R_UsMax, g_ServoDS3225MG_UsMax, g_ServoDS3225MG_UsMax, g_ServoMG996R_UsMax};     // callibration: 0<> ->Change  default value on setup
const int g_ServoCfgAttachDatasheetDegreeMax[g_ServoCount] = {g_ServoMG996R_DgMax, g_ServoMG996R_DgMax, g_ServoMG996R_DgMax, g_ServoDS3225MG_DgMax, g_ServoDS3225MG_DgMax, g_ServoMG996R_DgMax}; // callibration: 0<> ->Change  default value on setup
const int g_ServoCfgAttachMoveUsSteep[g_ServoCount] = {g_ServoSteepUs_Fast, g_ServoSteepUs_Default, g_ServoSteepUs_Default, g_ServoSteepUs_Slowly, g_ServoSteepUs_Slowly, g_ServoSteepUs_Slowly};

const int g_IdMuxSLed = 0;                                                   // ahora en desuso
const int g_IdMuxChanelServoBtnFnc01 = 0;                                    // 14;
const int g_IdMuxChanelServoBtnFnc02 = 8;                                    // 13;
                                                                             // const int g_IdMuxChanelServoBtnLeft[g_ServoCount] = {4, 10, 6, 1, 5, 3};     //{7,5,3,1,11,10};
const int g_IdMuxChanelServoBtnLeft[g_ServoCount] = {3, 5, 1, 6, 10, 4};     //{7,5,3,1,11,10};
                                                                             // const int g_IdMuxChanelServoBtnRight[g_ServoCount] = {12, 2, 14, 9, 13, 11}; //{6,4,2,0,9,8};
const int g_IdMuxChanelServoBtnRight[g_ServoCount] = {11, 13, 9, 14, 2, 12}; //{6,4,2,0,9,8};

const char *g_WifiSsid = "a-robot";
const char *g_WifiPwd = "123456789";
IPAddress g_WifiIpLocalP(192, 168, 1, 1);
IPAddress g_WifiIpGateway(192, 168, 1, 1);
IPAddress g_WifiIpMask(255, 255, 255, 0);
ClsCD74HC4067 g_Mux;
ClsServo g_Servo[g_ServoCount];
WebServer g_WebServer(80);

int g_counter = 0;
String fnc01_Servos();
String fnc02_Servos();
int g_fnc_IsRuning = 0; // 0=off, 1 move to site 0, 2 Move to site 2,
int g_fn02_CounterAct = -1;
int g_fn02_CounterMax = 4;

#endif