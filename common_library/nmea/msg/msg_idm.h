//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// IDM   Internal diagnostics message
//          1 2 3     n
//          | | |     |
// $PSKPIDM,x,x,x,...,x*hh
// 1) Message version (to disable different message parsing on sending an receiving sides)
// 2) Command ID
// 3) - n) message parameters
//////////////////////////////////////////////////////////////

#ifndef MSG_IDM_H
#define MSG_IDM_H

#include "nmea/nmea_message.h"


class MsgIDM : public NmeaMessage
{
public:
    MsgIDM();
    MsgIDM(int commandID, QList<QString> msgParameters);

    int messageVersion;
    int commandID;
    QList<QString> msgParameters;

    static const unsigned long IDMhash = 4801613;

    static const int msgVersion = 0;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgIDM * clone() {return new MsgIDM(*this);}
};

#endif
