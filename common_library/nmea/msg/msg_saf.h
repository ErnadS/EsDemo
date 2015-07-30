#ifndef MSG_SAF_H
#define MSG_SAF_H

#include "nmea/nmea_message.h"

class MsgSAF : public NmeaMessage
{
public:
    MsgSAF();
    MsgSAF(int outputFrom);


    int outputFrom;

    static const unsigned long SAFhash = 5456198;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSAF * clone() {return new MsgSAF(*this);}
};

#endif
