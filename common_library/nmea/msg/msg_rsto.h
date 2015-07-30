//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// RSTO   Reset Total traveled distance (to be used from service software only)
//
// no parameters
//////////////////////////////////////////////////////////////
#ifndef MSG_RSTO_H
#define MSG_RSTO_H

#include "nmea/nmea_message.h"

class MsgRSTO : public NmeaMessage
{
public:
    MsgRSTO();

    static const unsigned long RSTOhash = 5461071;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgRSTO * clone() {return new MsgRSTO(*this);}
};

#endif


