//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ROT Rate of turn
//         1  2 3
//         |  | |
// $--ROT,x.x,C*hh
// 1) Rate of turn, deg/min, "-" = bow turns to port
// 2) Status: A = data valid
//            V = data invalid
// 3) Checksum
//////////////////////////////////////////////////////////////
#ifndef MSG_ROT_H
#define MSG_ROT_H

#include "nmea/nmea_message.h"

class MsgROT : public NmeaMessage
{
public:
    MsgROT();
    MsgROT(float rateOfTurn, QString status);

    float rateOfTurn;                      // x.x = Rate of turn, deg/min, "-" = bow turns to port
    QString status;                        // A = Status


    static const unsigned long ROThash = 5394260;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgROT * clone() {return new MsgROT(*this);}
};

#endif
