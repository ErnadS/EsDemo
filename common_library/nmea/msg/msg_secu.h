//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// Serial Number Message (4800 baud)
//          1  2  3
//          |  |  |
// $PSKSNM,xx,xx,xx*hh
// 1) New desired serial number
// 2) Option number
// 3) Security code
//////////////////////////////////////////////////////////////

#ifndef MSG_SECU_H
#define MSG_SECU_H

#include "nmea/nmea_message.h"

class MsgSECU : public NmeaMessage
{
public:
    MsgSECU();
    MsgSECU(QString serial, int option, int code);

    QString serial;
    int option;
    int code;

    static const unsigned long SECUhash = 4539221;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSECU* clone() { return new MsgSECU(*this); }
};

#endif
