//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// MTW Water Temperature
//         1  2 3
//         |  | |
// $--MTW,x.x,C*hh
// 1) Degrees
// 2) Unit of Measurement, Celcius
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_MTW_H
#define MSG_MTW_H

#include "nmea/nmea_message.h"

class MsgMTW : public NmeaMessage
{
public:
    MsgMTW();
    MsgMTW(float waterTemperature, QString unitOfMeasurement);

    float waterTemperature;                // x.x = Degrees
    QString unitOfMeasurement;             // C = Unit of Measurement, Celcius


    static const unsigned long MTWhash = 5067863;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgMTW *clone() {return new MsgMTW(*this);}
};

#endif
