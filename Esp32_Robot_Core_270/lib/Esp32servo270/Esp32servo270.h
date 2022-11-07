/*
  Copyright (c) 2022 Vicente Niclos GNU:

  Based in:

  1.- Original Servo.h written by Michael Margolis in 2009
  2.- Copyright (c) 2017 John K. Bennett. All right reserved.
  Esp32servo270.h - Servo library for ESP32 - Version 1

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*
==========================================================================
You can dowload full project on
https://github.com/vniclos/Esp32-servo-270-degree
you can see all information on
https://github.com/vniclos/Esp32-servo-270-degree/wiki
*/
/*
// ========================================================================
// Limitations:
// ESP32 Only
// Maxim servo 16 servo objects can be created on the ESP32
// for connect servo recomended pwm GPIO PIN  [2,4,12-19,21-23,25-27,32-33]
// but if you use dev kit esp32 the pin 2 are used for blue led inside board
// ==========================================================================
  A servo is activated by creating an instance of the Servo class, and passing
  the desired GPIO pin to the attach() method, Attach has three call modes, short
  modes take default values
  The servos are pulsed in the background using the value most recently
  written using the write() method.

  The class methods are:
  ...................
    1 Instance of Servo
    Esp32servo270 - Class for manipulating instance of servo like
    Esp32servo270 myServo;
...................
    2 Attach servo
    There  are three modes
    2.1 Most simple
    int attach(attachEsp32Pin );
        attachEsp32Pin Attaches the given GPIO pin to the next free channel
        (channels that have previously been detached are used first),
        returns channel number or 0 if failure.
        All attachEsp32Pin numbers are allowed,  but only pins 2,4,12-19,21-23,25-27,32-33
        are recommended. and note pin 2 is used in ESP32 dev modules for led blue
        the omited parameter are replace for default values
        Set attachDatasheetUsMin pulse by #define ATTACH_DATASHEET_US_MIN_DEFAULT 1000
        Set attachDatasheetUsMax pulse by #define ATTACH_DATASHEET_US_MAX_DEFAULT 2000
        Set attachDatasheetDegreeMax degree turn by define ATTACH_DATASHEET_DEGREE_MAX_DEFAULT 180
        there are two additional parameters to limit the movement in degrees,
        these are to require the movements and avoid collisions in the place where
        they will be used
        Set attachMoveMin=0;
        Set attachMoveMax= attachDatasheetDegreeMax

    2.2 Atach medium
    int attach(int attachEsp32Pin, int attachDatasheetUsMin, int attachDatasheetUsMax, int attachDatasheetDegreeMax);
        enforced attachDatasheetUsMin  by #define US_DATASHEET_MinLimit 400
        enforced attachDatasheetUsMax  by #define US_DATASHEET_MaxLimit 2500
        enforced attachDatasheetDegreeMax by define:   #define DEGREE_DATASHEET_MinLimit 90 and  #define DEGREE_DATASHEET_MaxLimit 270

  2.3 Atach full parameters
   int attach(int attachEsp32Pin, int attachDatasheetUsMin, int attachDatasheetUsMax, int attachDatasheetDegreeMax, int attachMoveMin, int attachMoveMax);

        enforced attachMoveMin  by #define US_DATASHEET_MinLimit 400
        enforced attachMoveMax  by #define US_DATASHEET_MaxLimit 2500
        enforced degree by define:   #define DEGREE_DATASHEET_MinLimit 90 and  #define DEGREE_DATASHEET_MaxLimit 270
        enforced attachMoveMin=0;
        enforced attachMoveMax= attachMoveMax

.............
  3 int write(int value);
    move de servo to position
     if value is < US_DATASHEET_MinLimit its treated as an angle, otherwise as pulse width in microseconds
     in some case this values are enforced
            Value                                   Becomes
            -----                                   -------
            < 0                                     0
            [0 - 270]                               value (treated as degrees)
            [181 - 499]                             180 for dont break the servo
            [500 - (min-1)]                         attachDatasheetUsMin
            attachDatasheetUsMin-attachDatasheetUsMax             value (treated as microseconds)
            >ATTACH_DATASHEET_US_max0                         attachDatasheetUsMax

    void writeMicroseconds() - Sets the servo pulse width in microseconds.
        min and max are enforced (see above).
    int read() - Gets the last written servo pulse width as an angle between 0 and 180.
    int getPositionMicroseconds()   - Gets the last written servo pulse width in microseconds.
    bool getIsAtached() - Returns true if this servo instance is getIsAtached.
    void detach() - Stops an the getIsAtached servo, frees its getIsAtached pin, and frees
        its channel for reuse).

    *** ESP32-specific functions **
    setTimerWidth(value) - Sets the PWM timer width (must be 16-20) (ESP32 ONLY);
        as a side effect, the pulse width is recomputed.
    int getTimerWidth() - Gets the PWM timer width (ESP32 ONLY)
 */

#ifndef ESP32SERVO270_H
#define ESP32SERVO270_H

#define ESP32SERVO270_VERSION 1 // software version of this library

#define REFRESH_CPS 50
#define REFRESH_USEC 20000

//
// Range restriction of some values
// The limit prefix indicates that the variable cannot take a value above or below (Min =low, Max=upper)
#define SERVOS_COUNT_LIMIT 16 // no. of PWM channels in ESP32
#define DEGREE_DATASHEET_MinLimit 90
#define DEGREE_DATASHEET_MaxLimit 270
#define US_DATASHEET_MinLimit 400  // the shortest pulse sent to a servo
#define US_DATASHEET_MaxLimit 3000 // the longest pulse sent to a servo
//
// Default values
//#define PULSE_WIDTH_DEFAULT 1500         // default pulse width when servo is getIsAtached

#define TIMER_WIDTH_DEFAULT 16
#define TIMER_WIDTH_TICKS_DEFAULT 65536
#define PULSE_WIDTH_TICKS_DEFAULT 4825
#define ATTACH_DATASHEET_US_MIN_DEFAULT 500
#define ATTACH_DATASHEET_US_MAX_DEFAULT 2500
#define ATTACH_DATASHEET_DEGREE_MAX_DEFAULT 180
/*
// Usual values  for some usuall servos
// but you need read his datasheets (Change many times)
//------------------------------------------------------|
// MODEL     | μs Min  | μs Max   |  degree  |   volts  |
//-----------|---------|----------|----------|--------- |
// SG90      |  400    | 2400     | 180      |  4.8~5   |
// MG995     | 1000    | 2000     | 180      |  4.8~6   |
// MG996R    |  500    | 2500     | 180      |  4.8~7.2 |
// DS3225MG  |  500    | 2500     | 270      |  4.8~6.8 |
//----------------------------------------------------  |
// NOTE
//  in examples folder there / example named
// "es32Servo270_callibration" with this you can
// can easy calibrate your servo using web interface.
// Wiht it  the  ESP32 is configurede  access point,
// with 1223456789 password  and the url http://192.168.1.1
// show you a form for easy calibrate your servo.
//
//
// This group/channel/timmer mapping is for information only;
// |-------|--------|---------|---------|
// |  LEDC | Group  | Channel | Timer   |
// |-------|--------|---------|---------|
// |  0    |  0     |   0     |   0     |
// |  1    |  0     |   1     |   0     |
// |  2    |  0     |   2     |   1     |
// |  3    |  0     |   3     |   1     |
// |  4    |  0     |   4     |   2     |
// |  5    |  0     |   5     |   2     |
// |  6    |  0     |   6     |   3     |
// |  7    |  0     |   7     |   3     |
// |  8    |  1     |   0     |   0     |
// |  9    |  1     |   1     |   0     |
// | 10    |  1     |   2     |   1     |
// | 11    |  1     |   3     |   1     |
// | 12    |  1     |   4     |   2     |
// | 13    |  1     |   5     |   2     |
// | 14    |  1     |   6     |   3     |
// | 15    |  1     |   7     |   3     |
// |-------|--------|---------|---------|
 */

class Esp32servo270
{
public:
    Esp32servo270();
    // Arduino Servo Library calls
    int attach(int attachEsp32Pin); // attach the given pin to the next free channel, returns channel number or 0 if failure
    int attach(int attachEsp32Pin, int attachDatasheetUsMin, int attachDatasheetUsMax, int attachDatasheetDegreeMax);
    int attach(int attachEsp32Pin, int attachDatasheetUsMin, int attachDatasheetUsMax, int attachDatasheetDegreeMax, int attachMoveMin, int attachMoveMax, int AttachMovePosIni); // as above but also sets min and max values for writes. and max hardware degree admisible
    void detach();
    int write(int value);              // if value is < US_DATASHEET_MinLimit its treated as an angle, otherwise as pulse width in microseconds
    void writeMicroseconds(int value); // Write pulse width in microseconds

    // ESP32 only functions
    void setTimerWidth(int value); // set the PWM timer width (ESP32 ONLY)

    bool IsValidMoveTo(int iMoveTo); // return true if the last tray movement is in range valid position
    bool getIsAtached();             // return true if this servo is getIsAtached, otherwise false
    int getTimerWidth();             // get the PWM timer width (ESP32 ONLY)
    int getPositionDegree();         // returns current pulse width as an angle between 0 and 180 degrees

    int getPositionMicroseconds(); // returns current pulse width in microseconds for this servo

    int getAttachEsp32Pin();

    int getAttachDatasheetUsMin();
    int getAttachDatasheetUsMinLimit();

    int getAttachDatasheetUsMax();
    int getAttachDatasheetUsMaxLimit();

    int getAttachDatasheetDegreeMax();
    int getAttachDatasheetDegreeMaxLimit();
    int getAttachDegreeMinLimit();

    int getAttachMovePosIni();
    int getAttachMovePosMin();
    int getAttachMovePosMax();


private:
    int usToTicks(int usec);
    int ticksToUs(int ticks);
    static int ServoCount;    // the total number of getIsAtached servos
    static int ChannelUsed[]; // used to track whether a channel is in service
    int servoChannel = 0;     // channel number for this servo

    int timer_width = TIMER_WIDTH_DEFAULT;             // ESP32 allows variable width PWM timers
    int ticks = PULSE_WIDTH_TICKS_DEFAULT;             // current pulse width on this channel
    int timer_width_ticks = TIMER_WIDTH_TICKS_DEFAULT; // no. of ticks at rollover; varies with width

    int attachEsp32Pin = 0;                                     // GPIO pin assigned to this channel
    int attachDatasheetUsMin = ATTACH_DATASHEET_US_MIN_DEFAULT; // minimum pulse microsecconds  width for this servo
    int attachDatasheetUsMax = ATTACH_DATASHEET_US_MAX_DEFAULT; // maximum pulse microsecconds width for this servo
    int attachDatasheetDegreeMax = ATTACH_DATASHEET_DEGREE_MAX_DEFAULT;
    int AttachMovePosIni = -1; //-1 disable option
    int attachMovePosMin = 0;
    int attachMovePosMax = ATTACH_DATASHEET_DEGREE_MAX_DEFAULT;
};
#endif
