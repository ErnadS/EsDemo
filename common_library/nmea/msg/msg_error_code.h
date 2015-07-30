#ifndef MSG_ERROR_CODE_H
#define MSG_ERROR_CODE_H

#include "nmea/nmea_message.h"

class MsgERRORCODE : public NmeaMessage
{
public:
    MsgERRORCODE();
    MsgERRORCODE(unsigned errorCode, unsigned errorCount);

    unsigned errorCode;
    unsigned errorCount;

    static const unsigned long ERRORCODEhash = 5194821;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgERRORCODE * clone() {return new MsgERRORCODE(*this);}
};

#endif
