#ifndef MSG_DLR_H
#define MSG_DLR_H

#include "nmea/nmea_message.h"

class MsgDLR : public NmeaMessage
{
public:
    MsgDLR();

    MsgDLR(float longSpeedToWater_DL2, float transSpeedToWater_DL2, float resSpeedToWater_DL2,// float speedToWater_DL2_Direction,
           float longSpeedToGround_DL2, float transSpeedToGround_DL2, float resSpeedToGround_DL2, //float speedToGround_DL2_Direction,
           float speedToWater_DL1, bool bUsedGPS, bool bWC_fromGPS);


    // STW
    float longSpeedToWater_DL2;
    float transSpeedToWater_DL2;
    float resSpeedToWater_DL2;
    float speedToWater_DL2_Direction;

    // SOG
    float longSpeedToGround_DL2;
    float transSpeedToGround_DL2;
    float resSpeedToGround_DL2;
    float speedToGround_DL2_Direction;


    // DL1
    float speedToWater_DL1;

    bool    bUsedGPS; // true if SOG long, trans, res ... are calculated using GPS speed
    bool bWC_fromGPS; // true if WC is calculated using GPS speed

    static const unsigned long DLRhash = 4475986;

    bool setParams(QStringList m_message_parameters);

    QString getMsgBuffer();

    MsgDLR * clone() {return new MsgDLR(*this);}
};

#endif
