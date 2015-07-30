#ifndef MSG_CPPC_H
#define MSG_CPPC_H

#include "nmea/nmea_message.h"

class MsgCPPC : public NmeaMessage
{
public:
    MsgCPPC();

    int systemAck;

    static const unsigned long CPPChash = 5263427;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgCPPC * clone() {return new MsgCPPC(*this);}
};

#endif
