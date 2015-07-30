//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// TST   (unsure)
//          1  2   3   4  5   6
//          |  |   |   |  |   |
// $PSKPTST,x,xx,yxx.x,xx,ABCD,*hh
// 1) ID
// 2) ON/OFF can be 0, 1, 2 or 3
//      0 = test off and inject scanned, 
//      1 = test on and inject scanned,  
//      2 = test off and inject fixed,  // use this 2. Hold constant speed
//      3 = test on and inject fixed,
// 3) y= +-, x=Required speed
// 4) Format to return (not used), TX from 1 to 2, TX from 2 to 1. Where xx is 0, 1 or 2 
//      if 0 send speed from 1 and then -speed from 2 and then send result.
// 5) Output enable: ABCD (4 bytes, one for each msg type).
//      A = DAT
//      B = VBWF
//      C = MTWF
//      D = ALMA
// 6) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_TST_H
#define MSG_TST_H

#include "nmea/nmea_message.h"

class MsgTST : public NmeaMessage
{
public:
    MsgTST();
    MsgTST(int systemID, int onOff, float requiredSpeed, QString formatToReturn, QString outputsEnabled);
    
    int systemID;
    int onOff;                             // x = 0 - test off and inject scanned, 1 - test on and inject scanned, 2 - test off and inject fixed, 3 - test on and inject fixed.  
    float requiredSpeed;                   // yxxx - y= +-, x=Required speed
    QString formatToReturn;                // xx = Format to return (not used)
    QString outputsEnabled;                // DAT, VBWF, MTWF, ALMA


    static const unsigned long TSThash = 5526356;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgTST * clone() {return new MsgTST(*this);}
};

#endif
