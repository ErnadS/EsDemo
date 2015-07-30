#ifndef MSG_VMPCGTER_H
#define MSG_VMPCGTER_H

#include "nmea/nmea_message.h"

class MsgVMPCGTER : public NmeaMessage
{
public:
    MsgVMPCGTER();
    MsgVMPCGTER(int msgComand);

    int msgComand;

    static const unsigned long VMPCGTERhash = 5522770;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();


    MsgVMPCGTER * clone() {return new MsgVMPCGTER(*this);}
};

#endif
