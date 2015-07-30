//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// RSTT   Reset Trip Counter
//
// no parameters
//////////////////////////////////////////////////////////////
#ifndef MSG_RSTT_H
#define MSG_RSTT_H

#include "nmea/nmea_message.h"

class MsgRSTT : public NmeaMessage
{
public:
    MsgRSTT();

    static const unsigned long RSTThash = 5461076;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgRSTT * clone() {return new MsgRSTT(*this);}
};

#endif

