//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ACK Alert acknowledgement
//         1  2
//         |  |
// $--ACK,xxx*hh
// 1) Unique alarm number
// 2) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ACK_H
#define MSG_ACK_H

#include "nmea/nmea_message.h"

class MsgACK : public NmeaMessage
{
public:
    MsgACK();
    MsgACK(int uniqueAlarmNumber);

    int uniqueAlarmNumber;                 // xxx = Unique alarm number

    static const unsigned long ACKhash = 4277067;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();
    MsgACK*  clone() {return  new MsgACK(*this);}
};

#endif
