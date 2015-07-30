//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// HBT Heading – True
//         1  2  3
//         |  |  |
// $--HBT,x.x,T*hh
// 1) msg period:   (usualy 60 => we are sending hearbeat each 60 sec.
// 2) normal/demo:  'A' => equipment in normal operation; 'V'=> not in normal operation (as e.g. when system is in demo mode)
// 3) counter:      (0-9)

//////////////////////////////////////////////////////////////

#ifndef MSG_HBT_H
#define MSG_HBT_H

#include "nmea/nmea_message.h"

class MsgHBT : public NmeaMessage
{
public:
    MsgHBT();
    MsgHBT(int nHeartBeatPeriod, QString strValid, int nHeartBeatCounter);

    QString talkerId;

    int nHeartBeatPeriod;
    QString strValid;
    int nHeartBeatCounter;

    static const unsigned long HBThash = 4735572;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgHBT * clone() {return new MsgHBT(*this);}
};

#endif
