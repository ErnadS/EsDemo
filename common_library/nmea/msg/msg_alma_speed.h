//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// ALMA Speed (4800 baud)
//          1 2 3
//          | | |
// $01,xxxx*hh
// 1) Speed average, as xx.xx but without the decimal xxxx
// 2) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ALMA_SPEED_H
#define MSG_ALMA_SPEED_H

#include "nmea/nmea_message.h"

class MsgAlmaSpeed : public NmeaMessage
{
public:
    MsgAlmaSpeed();
    MsgAlmaSpeed(float speedAverage);

    //int systemID;
    float speedAverage;               // xxxx = Speed average but without the decimal "."
    float speedAverageWithDecimal;    // xx.xx = Speed average


    static const unsigned long ALMASPEEDhash = 1;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgAlmaSpeed* clone() {return new MsgAlmaSpeed(*this);}
};

#endif
