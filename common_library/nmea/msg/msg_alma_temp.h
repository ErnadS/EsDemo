//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// ALMA   Temp (4800 baud)
//      1  2
//      |  |
// $06,yyyy*hh
// 1) temperature as yyy.y but without decimal yyyy
// 2) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSGALMATEMP_H
#define MSGALMATEMP_H

#include "nmea/nmea_message.h"

class MsgAlmaTemp : public NmeaMessage
{
public:
    MsgAlmaTemp();
    MsgAlmaTemp(float tempereture);

    //int systemID;
    float tempereture;                // xxxx = Temperature but without the decimal "."
    float temperatureWithDecimal;     // xx.xx = Temperature


    static const unsigned long ALMASTEMPhash = 6;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgAlmaTemp * clone() {return new MsgAlmaTemp(*this);}
};

#endif // MSGALMATEMP_H
