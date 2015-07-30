//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// DTL    (4800 baud)
//           1     2     3     4     5     6    7
//           |     |     |     |     |     |    |
// $PSKDTL,+xx.x,+xx.x,+xx.x,+xx.x,+xx.x,+xx.x*hh
// 1) STW res Moving Average filter
// 2) SOG res Moving Average filter
// 3) STW res Moving Average With Slew Limit filter (Curtis)
// 4) SOG res Moving Average With Slew Limit filter (Curtis)
// 5) STW res Exponential filter (Jose)
// 6) SOG res Exponential filter (Jose)
// 7) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_DTL_H
#define MSG_DTL_H

#include "nmea/nmea_message.h"

class MsgDTL : public NmeaMessage
{
public:
    MsgDTL();

    MsgDTL(float sogGPS, float stwRes_MovAvg, float sogRes_MovAvg, float stwRes_MovAvgSlewLim,
           float sogRes_MovAvgSlewLim, float stwRes_ExpFilt, float sogRes_ExpFilt);


    float sogGPS;
    // Moving Average
    float stwRes_MovAvg;
    float sogRes_MovAvg;

    // Moving Average With Slew Rate Limit
    float stwRes_MovAvgSlewLim;
    float sogRes_MovAvgSlewLim;


    // Exponential Filter
    float stwRes_ExpFilt;
    float sogRes_ExpFilt;

    static const unsigned long DTLhash = 4478028;

    bool setParams(QStringList m_message_parameters);

    QString getMsgBuffer();

    MsgDTL * clone() {return new MsgDTL(*this);}
};

#endif
