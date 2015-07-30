#ifndef MSG_RCF_H
#define MSG_RCF_H

//////////////////////////////////////////////////////////////
// Skipper Sentence:
// ***********************************************************
// RCF   Result of Configuration (used by Service Sogtware)
// Answer on GCF received from ServiceSoftware
// $PSKPRCF,*hh
//////////////////////////////////////////////////////////////

#include "nmea/nmea_message.h"


class MsgRCF : public NmeaMessage
{
public:
    MsgRCF();
    MsgRCF(quint8 systemType, QString systemName, QString serialNo, QString ip, QString mac,
           QString sfi, QString destSfi, QString firmwareVer, quint8 group, QString dl2_serNo, QString dl2_firmwVer);

    quint8 systemType;
    QString systemName;
    QString serialNo;
    QString ip;
    QString mac;

    QString sfi;
    QString destSfi;
    quint8 group;
    QString firmwareVer;
    QString dl2_serNo;
    QString dl2_firmwVer;

    static const unsigned long RCFhash = 5391174;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

     MsgRCF * clone() {return new MsgRCF(*this);}
};


#endif
