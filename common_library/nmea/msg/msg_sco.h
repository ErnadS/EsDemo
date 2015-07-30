#ifndef MSGSCO_H
#define MSGSCO_H

#include "nmeamessage.h"

class MsgSCO : public NmeaMessage
{
public:
    MsgSCO();
    MsgSCO(QString sourceMacAddres, QString setupType);

    QString sourceMacAddres;
    QString setupType;


    static const unsigned long SCOhash = 5456719;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSCO * clone() {return new MsgSCO(*this);}
};

#endif // MSGSCO_H
