#include <Arduino.h>
#include "ClsServo.h"
#include <Esp32servo270.h>

ClsServo::ClsServo() { ; }
void ClsServo::Setup(int Id,
                     String Name,
                     String Model,

                     int MuxChanelButtonLeft,
                     int MuxChanelButtonRight,
                     int Esp32Pin,
                     int DatasheetUsMin,     // For map acurate degree movement using Map
                     int DatasheetUsMax,     // For map acurate degree movement using Map  0<>=Change  default value on setup
                     int DatasheetDegreeMax, //  For map acurate degree movement using Map 0= Change  default value on setup
                     int MovePosMin,
                     int MovePosMax,
                     int MovePosIni,
                     int MoveSteep)

{
#ifdef DEBUG
   Serial.println();
   Serial.print(" - ");
   Serial.print(Id);
   Serial.print(" - ");
   Serial.print(Name);
   Serial.print(" - ");
   Serial.print(MuxChanelButtonLeft);
   Serial.print(" - ");
   Serial.print(MuxChanelButtonRight);
   Serial.print(" - ");
   Serial.print(Esp32Pin);
   Serial.print(" - ");
   Serial.print(DatasheetUsMin);
   Serial.print(" - ");
   Serial.print(DatasheetUsMax);
   Serial.print(" - ");
   Serial.print(DatasheetDegreeMax);
   Serial.print(" - ");
   Serial.print(MovePosMin);
   Serial.print(" - ");
   Serial.print(MovePosMax);
   Serial.print(" - ");
   Serial.print(MovePosIni);
   Serial.print(" - ");
   Serial.println(MoveSteep);
#endif
   m_Id = Id;
   m_Name = Name;
   m_Model = Model;

   m_MuxChanelButtonLeft = MuxChanelButtonLeft;
   m_MuxChanelButtonRight = MuxChanelButtonRight;
   m_MoveSteep = MoveSteep;
   // digitalWrite(m_Pin, LOW);

   // int attach(int attachEsp32Pin, int attachDatasheetUsMin, int attachDatasheetUsMax, int attachDatasheetDegreeMax, int attachMoveMin, int attachMoveMax, int AttachMovePosIni); // as above but also sets min and max values for writes. and max hardware degree admisible
   void detach();
   m_Servo270.attach(Esp32Pin, DatasheetUsMin, DatasheetUsMax, DatasheetDegreeMax, MovePosMin, MovePosMax, MovePosIni);
   // debugSetup();
}
int ClsServo::getMoveLast() { return m_MoveLast; }
int ClsServo::getId() { return m_Id; }
int ClsServo::getMuxChanelButtonRight() { return m_MuxChanelButtonRight; }
int ClsServo::getMuxChanelButtonLeft() { return m_MuxChanelButtonLeft; }
String ClsServo::getName() { return m_Name; }
String ClsServo::getModel() { return m_Model; }
Esp32servo270 ClsServo::getServo270() { return m_Servo270; }

String ClsServo::getMsg() { return m_Msg; }

//==================================================================================
void ClsServo::debugSetup()
{
   Serial.println("ClsServo.Debug");
   // change int PosActReaded = m_Servo.read();
   int PosActReaded = m_Servo270.getPositionDegree();
   Serial.print("Id=");
   Serial.print(m_Id);

   Serial.print(" Name=");
   Serial.print(m_Name);
   Serial.print(" Model=");
   Serial.print(m_Model);
   Serial.print(" getEsp32Pin=");
   Serial.print(m_Servo270.getAttachEsp32Pin());

   Serial.print(" getDatasheetUsMin=");
   Serial.print(m_Servo270.getAttachDatasheetUsMin());
   Serial.print(" getDatasheetUsMax=");
   Serial.print(m_Servo270.getAttachDatasheetUsMax());

   Serial.print(" getAttachMovePosMin= ");
   Serial.print(m_Servo270.getAttachMovePosMin());
   Serial.print(" getAttachMovePosMax= ");
   Serial.print(m_Servo270.getAttachMovePosMax());
   Serial.print(" getAttachMovePosIni= ");
   Serial.print(m_Servo270.getAttachMovePosIni());

   Serial.print(" m_MoveSteep= ");
   Serial.print(m_MoveSteep);

   Serial.print(" MuxChanelLeft=");
   Serial.print(m_MuxChanelButtonLeft);
   Serial.print(" MuxChanelRight=");
   Serial.print(m_MuxChanelButtonRight);
}

String ClsServo::Goto(int PosGoto)
{
   m_Msg = "";
   int iPosAct = -1;
   int iPosGoto = -1;
   iPosAct = m_Servo270.getPositionMicroseconds();
   iPosGoto = PosGoto;
#ifdef DEBUG
   Serial.println("");
   Serial.print("ClsServo::Goto Id=" + String(m_Id) + " " + m_Name + " getAttachMovePosMin=" + String(m_Servo270.getAttachMovePosMin()) + " getAttachMovePosMax=" + String(m_Servo270.getAttachMovePosMax()));
   Serial.print(" iPosAct= ");
   Serial.print(iPosAct);
   Serial.print(" iPosGoto= ");
   Serial.println(iPosGoto);
#endif
   if (iPosGoto < m_Servo270.getAttachMovePosMin())
   {
      m_Msg = m_Name + ": Oops! No puedo moverme! Estoy en " + String(iPosAct) + " y mi minimo es " + String(m_Servo270.getAttachMovePosMin());
      return m_Msg;
   }
   if (iPosGoto > m_Servo270.getAttachMovePosMax())
   {
      m_Msg = m_Name + ": Oops! No puedo moverme! Estoy en " + String(iPosAct) + " y mi maximo es " + String(m_Servo270.getAttachMovePosMax());

      return m_Msg;
   }
   m_MoveLast = iPosGoto;
   m_Servo270.write(iPosGoto);
 
   Serial.print(m_Name);
   Serial.print(" goto{ ");
   Serial.print(m_Id);
   Serial.print(", ");
   Serial.print(iPosGoto);
   Serial.println(" }");

   m_Msg = String(m_Id + " ") + m_Name + " ir a " + String(PosGoto) + ": Ok. Me he movido  de  " + String(iPosAct) + " a " + String(m_Servo270.getPositionMicroseconds()) + ". [" + String(m_Servo270.getAttachMovePosMin()) + " - " + String(m_Servo270.getAttachMovePosMax()) + "]";
   return m_Msg;
}
//==========================================
//==========================================

String ClsServo::DoCommand(String Cmd)
{

   String HtmlResult = "";
   Cmd.toLowerCase();

   int iPosGoto = -1; // not move
   int iPosAct = (m_Servo270.getPositionMicroseconds());
   String ifCmd = "";
   if (Cmd == "der")
   {
      ifCmd = " if-der";
      iPosGoto = iPosAct + m_MoveSteep;
   }
   if (Cmd == "izq")
   {
      ifCmd = "> if-izq";
      iPosGoto = iPosAct - m_MoveSteep;
   }
   if (Cmd == "min")
   {
      ifCmd = " if-min";
      iPosGoto = (m_Servo270.getAttachMovePosMin());
   }
   if (Cmd == "max")
   {
      ifCmd = " if-max";
      iPosGoto = m_Servo270.getAttachMovePosMax();
   }
   if (Cmd == "ini")
   {
      ifCmd = " if-ini";
      iPosGoto = m_Servo270.getAttachMovePosIni();
   }
   if (iPosGoto != -1)
   {

#ifdef DEBUG
      Serial.println("");
      Serial.print("ClsServo.WebHandleCommand {");
      Serial.print(m_Id);
      Serial.print(", ");
      Serial.print(iPosGoto);
      Serial.print("} " + m_Name + " cmd=" + Cmd);
      Serial.print(" ifcmd= " + ifCmd);
      Serial.print(" ordeno mover de  ");
      Serial.print(iPosAct);
      Serial.print(" hasta ");
      Serial.print(iPosGoto);
      Serial.println("");
#endif
      Goto(iPosGoto);
   }

   return m_Msg;
}
void ClsServo::MoveToIni()
{
   Goto(m_Servo270.getAttachMovePosIni());
}
//---------------------------------------------------------
void ClsServo::MoveToSlowly(int posGoto, int delaySteep)
{

   int iPosAct = m_Servo270.getPositionMicroseconds();


   if (posGoto < iPosAct)
   {

      for (int i = iPosAct; i > posGoto; i--)
      {

         Goto(i);
         delay(delaySteep);
      }
   }
   if (posGoto > iPosAct)
   {


      for (int i = iPosAct; i < posGoto; i++)
      {

         Goto(i);
         delay(delaySteep);
      }
   }

}
