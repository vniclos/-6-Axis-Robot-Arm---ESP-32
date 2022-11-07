
#ifndef ClsCD74HC4067_H
#define ClsCD74HC4067_H
#include <Arduino.h>

// https://github.com/waspinator/CD74HC4067/blob/master/src/CD74HC4067.cpp
class ClsCD74HC4067
{
public:
  ClsCD74HC4067();
  void setup(int pinS0, int pinS1, int pinS2, int pinS3, int pinSig, int pinEn);
 // void debug(int idChanel, int val);
 #ifdef DEBUG
  void debugAll(unsigned int counter);
  #endif
  void loop();
  int muxDigitalRead(int idChanel);
  void muxDigitalWrite(int idChanel, int Value);
  int loop(int idChanel);
  int  getLoopReadedChanel(int idChanel);
private:
  //void debugAllId(unsigned int counter);
  void channelSelect(int channel);
  int m_PinControl[4] = {0, 0, 0, 0};
  int m_PinSig = 0;
  int m_PinEn = 0;
  int m_channelSelected;

  int m_ValuesReaded[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  int m_ValueRead;
  int m_channel_table[16][4] = {
      // s0, s1, s2, s3     channel
      {0, 0, 0, 0}, // 0
      {1, 0, 0, 0}, // 1
      {0, 1, 0, 0}, // 2
      {1, 1, 0, 0}, // 3
      {0, 0, 1, 0}, // 4
      {1, 0, 1, 0}, // 5
      {0, 1, 1, 0}, // 6
      {1, 1, 1, 0}, // 7
      {0, 0, 0, 1}, // 8
      {1, 0, 0, 1}, // 9
      {0, 1, 0, 1}, // 10
      {1, 1, 0, 1}, // 11
      {0, 0, 1, 1}, // 12
      {1, 0, 1, 1}, // 13
      {0, 1, 1, 1}, // 14
      {1, 1, 1, 1}  // 15
  };
};
#endif