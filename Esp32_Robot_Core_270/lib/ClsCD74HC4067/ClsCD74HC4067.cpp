#include <Arduino.h>
#include "ClsServo.h"
#include <ClsCD74HC4067.h>
ClsCD74HC4067::ClsCD74HC4067() { ; }
void ClsCD74HC4067::setup(int pinS0, int pinS1, int pinS2, int pinS3, int pinSig, int PinEn)
{
   m_PinEn = PinEn;
   m_PinSig = pinSig;
   m_PinControl[0] = pinS0;
   m_PinControl[1] = pinS1;
   m_PinControl[2] = pinS2;
   m_PinControl[3] = pinS3;
   digitalWrite(m_PinEn, LOW);
   for (int i = 0; i < 4; i++)
   {
      pinMode(m_PinControl[i], OUTPUT);
      digitalWrite(m_PinControl[i], LOW);
   }
}
int ClsCD74HC4067::muxDigitalRead(int idChanel)
{
   for (int i = 0; i < 4; i++)
   {
      digitalWrite(m_PinControl[i], m_channel_table[idChanel][i]);
      delay(1); // 100,50,25
   }
   digitalWrite(m_PinSig, LOW);
   delay(1); // 300,150,75,30
   int val = digitalRead(m_PinSig);

   return val;
}

void ClsCD74HC4067::muxDigitalWrite(int idChanel, int Value)
{
   for (int i = 0; i < 4; i++)
   {
      digitalWrite(m_PinControl[i], m_channel_table[idChanel][i]);
   }
   digitalWrite(m_PinSig, Value); // return the value
}

//==================================================================================
#ifdef DEBUG
void ClsCD74HC4067::debugAll(unsigned int counter)
{

   Serial.println("-----------");

   Serial.print("Mux=   ");
   for (int i = 0; i < 16; i++)
   {
      Serial.print(i % 10);
      Serial.print("   ");
   }
   Serial.println("");

   Serial.print(counter);
   Serial.print("==   ");
   loop();
   for (int i = 0; i < 16; i++)
   {
      Serial.print(m_ValuesReaded[i]);
      Serial.print("   ");
   }

   Serial.println("");
}
#endif
void ClsCD74HC4067::loop()
{
   for (int idChanel= 0; idChanel < 16; idChanel++)
   {
      int val = muxDigitalRead(idChanel);

      m_ValuesReaded[idChanel] = val;
   }
}
 int  ClsCD74HC4067::getLoopReadedChanel(int idChanel)
 {
return m_ValuesReaded[idChanel];

 }
