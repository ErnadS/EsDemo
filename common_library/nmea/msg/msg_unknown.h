#ifndef MSG_UNKNOWN_H
#define MSG_UNKNOWN_H

#include "nmea/nmea_message.h"

class MsgUnknown : public NmeaMessage
{
public:
    MsgUnknown(QString messageType);

    bool setParams(QStringList m_message_parameters);
    static const unsigned long UNKNOWNhash = 0;

    QString getMsgBuffer();

    MsgUnknown * clone() {return new MsgUnknown(*this);}
};

#endif
