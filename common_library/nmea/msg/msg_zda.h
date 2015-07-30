//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ZDA Time and date
//            1     2   3  4   5  6   7
//            |     |   |  |   |  |   |
// $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh
// 1) Time (UTC)
// 2) Day, 01 to 31 (UTC)
// 3) Month, 01 to 12 (UTC)
// 4) Year (UTC)
// 5) Local zone hours, 00 to +/-13
// 6) Local zone minutes, 00 to +-59
// 7) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ZDA_H
#define MSG_ZDA_H

#include "nmea/nmea_message.h"

class MsgZDA : public NmeaMessage
{
public:
    MsgZDA();
    MsgZDA(QString time, int day, int month, int year, int localZoneHours, int LocalZoneMinutes);

    QString time;
    int day;                                    // Two digits fixed, i.e. leading zero
    int month;                                  // Two digits fixed, i.e. leading zero
    int year;                                   // Four digits fixed, i.e. no leading zero
    int localZoneHours;                         // Two digits fixed, i.e. leading zero
    int LocalZoneMinutes;                       // Two digits fixed, i.e. leading zero

    static const unsigned long ZDAhash = 5915713;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgZDA * clone() {return new MsgZDA(*this);}
};

#endif
