//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ALR Alarm
//            1      2  3 4  5   6
//            |      |  | |  |   |
// $--ALR,hhmmss.ss,xxx,A,A,c--c*hh
// 1) Time of alarm (UTC)
// 2) Unique alarm number
// 3) Alarm condition
// 4) Alarm acknowledge state
// 5) Alarm description, text
// 6) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ALR_H
#define MSG_ALR_H

#include "nmea/nmea_message.h"

class MsgALR : public NmeaMessage
{
public:
    MsgALR();
    MsgALR(QString timeOfAlarm, QString uniqueAlarmNumber, QString alarmCondition, QString alarmAcknowledgeState, QString alarmDescription);

    QString timeOfAlarm;                   // hhmmss.ss = Time of alarm (UTC)
    QString uniqueAlarmNumber;             // xxx = Unique alarm number  // !!! Changed to string. It can be empty parameter
    QString alarmCondition;                // A = Alarm condition
    QString alarmAcknowledgeState;         // A = Alarm acknowledge state
    QString alarmDescription;              // c--c = Alarm description, text


    static const unsigned long ALRhash = 4279378;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgALR *clone() {return new MsgALR(*this);}
};

#endif
