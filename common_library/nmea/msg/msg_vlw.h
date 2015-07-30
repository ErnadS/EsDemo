//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// VLW Distance Traveled through Water
//         1  2  3  4 5
//         |  |  |  | |
// $--VLW,x.x,N,x.x,N*hh
// 1) Total cumulative water distance
// 2) N = Nautical Miles
// 3) Water distance since Reset
// 4) N = Nautical Miles
// 5) Total cumulative ground distance
// 6) N = Nautical Miles
// 7) Ground distance since Reset
// 8) N = Nautical Miles
// 9) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_VLW_H
#define MSG_VLW_H

#include "nmea/nmea_message.h"

class MsgVLW : public NmeaMessage
{
public:
    MsgVLW();
    MsgVLW(float totCumulativeWaterDist, QString totCumulativeWaterDistUnit, float waterDistSinceReset,
           QString waterDistSinceResetUnit, float totCumulativeGroundDist, QString totCumulativeGroundDistUnit,
           float groundDistSinceReset, QString groundDistSinceResetUnit);

    float totCumulativeWaterDist;                // x.x = Total cumulative water distance
    QString totCumulativeWaterDistUnit;          // N = Nautical Miles
    float waterDistSinceReset;                   // x.x = Water distance since Reset
    QString waterDistSinceResetUnit;             // N = Nautical Miles
    float totCumulativeGroundDist;               // x.x = Total cumulative ground distance
    QString totCumulativeGroundDistUnit;         // N = Nautical Miles
    float groundDistSinceReset;                  // x.x = Ground distance since Reset
    QString groundDistSinceResetUnit;            // N = Nautical Miles


    static const unsigned long VLWhash = 5655639;

    bool setParams(QStringList m_message_parameters);
    virtual QString getMsgBuffer();

    MsgVLW * clone() {return new MsgVLW(*this);}
};

#endif
