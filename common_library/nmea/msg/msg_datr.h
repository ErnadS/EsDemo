#ifndef MSG_DATR_H
#define MSG_DATR_H

#include "nmea/nmea_message.h"

class MsgDATR : public NmeaMessage
{
public:
    MsgDATR();
    MsgDATR(float latitude, QString northOrSouth, float longitude, QString eastOrWest, QString utcOfData
            ,float sog, float cog, float depth, float depthMode, quint32 nCurrentSeaCalibLeg, quint32 nCurrentSeaCalibDistance);


    float latitude;
    QString northOrSouth;
    float longitude;
    QString eastOrWest;
    QString utcOfData;

    float sog;
    float cog;
    float depth;

    float depthMode;
    quint32 nCurrentSeaCalibLeg;
    quint32 nCurrentSeaCalibDistance;

    static const unsigned long DATRhash = 4281426;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgDATR * clone() {return new MsgDATR(*this);}
};

#endif
