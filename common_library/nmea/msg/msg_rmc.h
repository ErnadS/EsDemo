//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// RMC Recommended minimum specific GNSS data
//          1       2    3    4    5    6  7   8    9   10  11 12 13 14
//          |       |    |    |    |    |  |   |    |    |   | |  |  |
// $--RMC,hhmmss.ss,A,xxxx.xx,a,xxxx.xx,a,x.x,x.x,ddmmyy,x.x,a,a, a*hh
// 1) Time (UTC)
// 2) Status ( A = data valid, V = navigation receiver warning )
// 3) Latitude
// 4) N or S (North or south)
// 5) Longitude
// 6) E or W (East or West)
// 7) Speed over ground, knots
// 8) Course over ground, degrees true
// 9) Date dd/mm/yy
// 10) Magnetic variation
// 11) E or W, E = Easterly variation subtracts from True course, W = Westerly adds to True course
// 12) Mode indicator
// 13) Navigational status
// 14) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_RMC_H
#define MSG_RMC_H

#include "nmea/nmea_message.h"

class MsgRMC : public NmeaMessage
{
public:
    MsgRMC();

    MsgRMC(QString time, QString status, float latitude, QString northOrSouth, float longitude,
           QString eastOrWest, float speedOverGround, float courseOverGround, QString date, float magneticVariation,
           QString magVarEastOrWest, QString modeIndicator, QString navigationalStatus);

    QString talkerID;
    QString time;
    QString status;
    float latitude;
    QString northOrSouth;
    float longitude;
    QString eastOrWest;
    float speedOverGround;
    float courseOverGround;
    QString date;
    float magneticVariation;
    QString magVarEastOrWest;
    QString modeIndicator;
    QString navigationalStatus;

    static const unsigned long RMChash = 5393731;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgRMC * clone() {return new MsgRMC(*this);}
};

#endif
