//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// HDT Heading – True
//         1  2  3
//         |  |  |
// $--HDT,x.x,T*hh
// 1) Heading Degrees, true
// 2) T = True
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_HDT_H
#define MSG_HDT_H

#include "nmea/nmea_message.h"

class MsgHDT : public NmeaMessage
{
public:
    MsgHDT();
    MsgHDT(float headingDegrees, QString statusTrue);

    float headingDegrees;                  // x.x = Heading Degrees, true
    QString statusTrue;                    // T = True


    static const unsigned long HDThash = 4736084;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgHDT * clone() {return new MsgHDT(*this);}
};

#endif
