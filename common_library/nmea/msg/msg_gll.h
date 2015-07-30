//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// GLL – Geographic position – Latitude/Longitude
//           1    2    3    4    5      6 7 8
//           |    |    |    |    |      | | |
// $--GLL,xxxx.xx,a,xxxx.xx,a,hhmmss.ss,A,a*hh
// 1) Latitude
// 2) N/S
// 3) Longitude
// 4) E/W
// 5) UTC of position
// 6) Status
// 7) Mode indicator
// 8) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_GLL_H
#define MSG_GLL_H

#include "nmea/nmea_message.h"

class MsgGLL : public NmeaMessage
{
public:
    MsgGLL();
    MsgGLL(float latitude, QString northOrSouth, float longitude, QString eastOrWest, QString utcOfPosition,
           QString status, QString modeIndicator);

    float latitude;
    QString northOrSouth;
    float longitude;
    QString eastOrWest;
    QString utcOfPosition;
    QString status;
    QString modeIndicator;

    static const unsigned long GLLhash = 4672588;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgGLL * clone() {return new MsgGLL(*this);}

};

#endif
