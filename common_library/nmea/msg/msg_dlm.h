#ifndef MSG_DLM_H
#define MSG_DLM_H

#include "nmea/nmea_message.h"

class MsgDLM : public NmeaMessage
{
public:
    MsgDLM();
    MsgDLM(float rateOfTurn, float headingTrue, float transAftSpeedToWater, float transAftSpeedToGround,
           float resCurrentSpeed, float currentDirection, int nDraftType, float gpsSog, float roll,
           float pitch, float gpsSogAngle);

    float rateOfTurn;
    float headingTrue;

    float transAftSpeedToWater;
    float transAftSpeedToGround;

    float resCurrentSpeed;
    float currentDirection;

    int nDraftType;

    float gpsSog;
    float roll;
    float pitch;
    float gpsSogAngle;


    static const unsigned long DLMhash = 4475981;

    bool setParams(QStringList m_message_parameters);

    QString getMsgBuffer();

    MsgDLM * clone() {return new MsgDLM(*this);}
};

#endif
