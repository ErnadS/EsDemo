//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// MTWF Temp from sensor
//             1  2  3
//             |  |  |
// $PSKPMTWF,xx.x,C*nn
// 1) Temperature degrees C
// 2) Centigrade
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_MTWF_H
#define MSG_MTWF_H

#include "nmea/nmea_message.h"

class MsgMTWF : public NmeaMessage
{
public:
    MsgMTWF();
    MsgMTWF(float temperature, QString centigrade);

    //int systemID;
    float temperature;                     // xx.x = Temperature degrees C
    QString centigrade;                    // C = Centigrade

    static const unsigned long MTWFhash = 5527366;
    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgMTWF * clone() {return new MsgMTWF(*this);}
};

#endif
