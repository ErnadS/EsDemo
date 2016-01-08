#ifndef MSG_NLRT_H
#define MSG_NLRT_H

#include "nmea/nmea_message.h"

class Msg_Nlrt : public NmeaMessage
{
public:
    Msg_Nlrt();

    static const unsigned long NLRTFhash = 0; // TODO:

    virtual QString getMsgBuffer();

    bool setParams(QStringList m_message_parameters);
    Msg_Nlrt * clone() {return new Msg_Nlrt(*this);}
};

#endif // MSG_NLRT_H
