#ifndef MSG_DLI_H
#define MSG_DLI_H

#include "nmea/nmea_message.h"

class MsgDLI : public NmeaMessage
{
public:
    MsgDLI();

    MsgDLI(float total, float trip,
           int nDepthType,  // if 2 => 2 axis (forward and right), if '4' => 4 axis
           float frAxisDepthFwd_DL2, float frAxisDepthAft_DL2, // used both when 2 and 4 axis
           float scAxisDepthFwd_DL2, float scAxisDepthAft_DL2, // used only if 4 axis (if "nDepthType" = 4)
           float depthAverage, float temperature, QString hours, QString minuts);


    //////////////////////////////////////////////////////////////////////
    // Total/Trip
    //////////////////////////////////////////////////////////////////////
    float total;
    float trip;

    //////////////////////////////////////////////////////////////////////
    // DEPTH
    //////////////////////////////////////////////////////////////////////
    quint8 nDepthType;  // 2 or 4 (2 axis or 4 axis)

    float frAxisDepthFwd_DL2;
    float frAxisDepthAft_DL2;
    float scAxisDepthFwd_DL2;
    float scAxisDepthAft_DL2;

    float depthAverage;

    // other info
    float temperature;

    QString hours;
    QString minuts;

    static const unsigned long DLIhash = 4475977;

    bool setParams(QStringList m_message_parameters);

    QString getMsgBuffer();

    MsgDLI * clone() {return new MsgDLI(*this);}
};

#endif
