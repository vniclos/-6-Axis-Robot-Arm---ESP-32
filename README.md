# -6-Axis-Robot-Arm---ESP-32
6 axis robot managed by wifi and buttons, using ESP32
You can use wifi enviorment or buttons for manage this robot

![](https://github.com/vniclos/-6-Axis-Robot-Arm---ESP-32/blob/main/docs/robot_6doi%20(2).jpg?raw=true)

**Hardware**
- ESP32 DEV KIT
- MUX CD74HC4067 16 Channels
- 14 push buttons
- 2 Led
- 1 Power suppy 220-5v 16a 
- Swith for power supply (220v)
- Some wire 
- some things for game like small cubes (show image below)

**Wire**

![](https://raw.githubusercontent.com/vniclos/-6-Axis-Robot-Arm---ESP-32/ae0b1cbcc480b43f404f113b8816cadb866c05e8/docs/robot%206_bb.svg)


### GPIO pins used 
Are configured in file main_defines.h

- for led internal join to external

```c
  const int g_PinLedBlue = 2;
```
- For servos  are defined in main_defines.h
```c
const int g_PinsServo[6] = {21, 4, 19, 32, 23, 33};
```
- For on ESP32 to jon mux CD74HC4067 (Usen for Buttons)
```c
const int g_PinsMuxSEn = 25;                  
const int g_PinsMuxSig = 13;                  
const int g_PinsMuxS0_4[] = {26, 27, 14, 12}; 
```
### Wifi configuration 
Are configured in file main_defines.h
```c
const char *g_WifiSsid = "a-robot";
const char *g_WifiPwd = "123456789";
IPAddress g_WifiIpLocalP(192, 168, 1, 1);
IPAddress g_WifiIpGateway(192, 168, 1, 1);
IPAddress g_WifiIpMask(255, 255, 255, 0);
```

### Asignation buttons (Chanels mux) to servos and functions
```c
const int g_IdMuxChanelServoBtnFnc01 = 0; // Function go robot to initial position
const int g_IdMuxChanelServoBtnFnc02 = 8; // Funtion robot do automatic secuence of movements
                                                                             
const int g_IdMuxChanelServoBtnLeft[g_ServoCount] = {3, 5, 1, 6, 10, 4};     //chanels for move left sevos 0-5
const int g_IdMuxChanelServoBtnRight[g_ServoCount] = {11, 13, 9, 14, 2, 12}; //chanels for move right sevos 0-5
```

### Servos initial configuration 
```c
// Arrays for config servos 0 to 5 
const String g_ServoCfgModel[6] = {"MG996R", "MG996R", "MG996R", "DS3225MG", "DS3225MG", "MG996R"};
const int g_ServoCfgAttachMoveMin[6] = {600, 1200, 700, 950, 1120, 600};     // minimun millis movement 
const int g_ServoCfgAttachMoveIni[6] = {800, 1500, 1180, 1150, 1400, 1270};  // Intial position millis movement 
const int g_ServoCfgAttachMoveMax[6] = {1160, 1800, 2000, 1560, 1550, 1472}; // minimun millis movement

// secuence Movement for get cube, (Starting from inital position)
int g_moves_01[7][2] =   {{0, 600}, {3, 1520},  {2, 1798}, {4, 1363}, {0, 1035}, {4, 1500}, {3, 1171}};
// secuence Movement for set  cube in position 0, (Starting from pick position)
int g_moves_02_0[8][2] = {{5, 1450}, {2, 1048}, {3, 1410}, {4, 1130}, {1, 1639}, {0, 663},  {2, 1000}, {4, 1270}}; 
// secuence Movement for set  cube in position 1, (Starting from pick position)
int g_moves_02_1[8][2] = {{5, 1295}, {2, 1464}, {3, 1280}, {4, 1189}, {1, 1639}, {0, 663}, {2, 1000}, {4, 1270}}; 
// secuence Movement for set  cube in position 2, (Starting from pick position)
int g_moves_02_2[8][2] = {{5, 1103}, {2, 1066}, {3, 1377}, {4, 1123}, {1, 1374}, {0, 663}, {2, 1000}, {4, 1270}}; 
// secuence Movement for set  cube in position 3, (Starting from pick position)
int g_moves_02_3[8][2] = {{5, 1149}, {2, 1320}, {3, 1551}, {4, 1285}, {1, 1382}, {0, 663}, {2, 1200}, {4, 1270}};
// secuence Movement for set  cube in position 4, (Starting from pick position)
int g_moves_02_4[8][2] = {{5, 1377}, {2, 1510}, {3, 1347}, {4, 1225}, {1, 1255}, {0, 663}, {2, 1200}, {4, 1270}};
```
