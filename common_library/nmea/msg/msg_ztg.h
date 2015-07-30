//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ZTG UTC and time to destination waypoint
//          1             2     3   4
//          |             |     |   |
// $--ZTG,hhmmss.ss,hhmmss.ss,c--c*hh
// 1) UTC of observation
// 2) Time to go, hh = 00 to 99 ( mm = 00 to 99, ss = = 00 to 99 ?)
// 3) Destination waypoint ID
// 4) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ZTG_H
#define MSG_ZTG_H

#include "nmea/nmea_message.h"

class MsgZTG : public NmeaMessage
{
public:
    MsgZTG();
    MsgZTG(QString time, QString timeToGo, QString destinationWaypointID);

    QString time;
    QString timeToGo;
    QString destinationWaypointID;


    static const unsigned long ZTGhash = 5919815;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgZTG * clone() {return new MsgZTG(*this);}
};

#endif
