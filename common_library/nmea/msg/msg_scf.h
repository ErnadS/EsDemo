#ifndef MSG_SCF_H
#define MSG_SCF_H

#include "nmea/nmea_message.h"

class MsgSCF : public NmeaMessage
{
public:
    MsgSCF();
    MsgSCF(QString systemName, QString ip, QString sfi, QString destSfi, quint8 group);

    QString systemName;
    QString ip;
    QString sfi;
    QString destSfi;
    quint8 group;

    static const unsigned long SCFhash = 5456710;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSCF * clone() {return new MsgSCF(*this);}
};

#endif
