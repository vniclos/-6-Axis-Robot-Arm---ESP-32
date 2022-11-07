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


#pins used 
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
