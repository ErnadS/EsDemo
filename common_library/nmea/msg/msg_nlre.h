#ifndef MSG_NLRE_H
#define MSG_NLRE_H

#include "nmea/nmea_message.h"

class Msg_Nlre : public NmeaMessage
{
public:
    Msg_Nlre();

    static const unsigned long NLREhash = 0; // TODO:

    virtual QString getMsgBuffer();

    bool setParams(QStringList m_message_parameters);
    Msg_Nlre * clone() {return new Msg_Nlre(*this);}

};

#endif // MSG_NLRE_H
