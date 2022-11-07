#ifndef CLSSERVO_H
#define CLSSERVO_H
#include <Arduino.h>
#include <Esp32servo270.h>

class ClsServo
{
private:
    String m_Name = "No name";
    String m_Model = "";
    int m_Id = 0;
    int m_MuxChanelButtonLeft = 0;
    int m_MuxChanelButtonRight = 0;
    int m_MoveLast = 0;
    int m_MoveSteep = 1;
    String m_Msg = "";
    Esp32servo270 m_Servo270;

public:
    ClsServo();
    // int (int Esp32Pin, int DatasheetUsMin, int DatasheetUsMax, int DatasheetDegreeMax, int MoveDegreeMin, int MoveDegreeMax); // as above but also sets min and max values for writes. and max hardware degree admisible

    void Setup(int Id,
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
               int MovePosSteep);

    // void loop(int addDegree);
    String DoCommand(String Cmd);
    // void Setup(int Id, String Name, int Pin, long IntervalMillisSlot);
    void debugSetup();
    Esp32servo270 getServo270();
    int getId();
    int getMuxChanelButtonRight();
    int getMuxChanelButtonLeft();
    String getName();
    String getModel();
    String getMsg();
    String Goto(int Pos);
    int getMoveLast();
    bool IsMoving();
    void MoveToIni();
    void MoveToSlowly(int posGoto, int delaySteep);
};
#endif