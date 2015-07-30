//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ARC Alert command refused
//            1      2   3   4  5  6
//            |      |   |   |  |  |
// $--ARC,hhmmss.ss,aaa,x.x,x.x,c*hh
// 1) Release time of Alert Command Refuse  (ignore or should support all alternatives?)
// 2) 7u of the alert zo distinguish alerts of the same type and from the same source)
// 5) Refuse Alert Command
//    A:       acknowledge
//    Q:       request/repeat information
//    O:       responsibility transfer
//    S:       silence
// 6) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ARC_H
#define MSG_ARC_H

#include "nmea/nmea_message.h"

class MsgARC : public NmeaMessage
{
public:
    MsgARC();
    MsgARC(QString releaseTime, int manufacturerMnemonicCode, unsigned long alertIdentifier,
    unsigned long alertInstance, QString refusedAlertCommand);

    QString releaseTime;
    int manufacturerMnemonicCode;
    unsigned long alertIdentifier;
    unsigned long alertInstance;
    QString refusedAlertCommand;

    static const unsigned long ARChash = 4280899;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();
    MsgARC *clone() {return new MsgARC(*this);}
};

#endif
