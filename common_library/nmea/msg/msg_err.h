#ifndef MSG_ERR_H
#define MSG_ERR_H

#include "nmea/nmea_message.h"


class MsgErr : public NmeaMessage
{
public:
    MsgErr();
    MsgErr(NmeaMessageErrorType m_error_id);

    bool setParams(QStringList m_message_parameters);

    QString getMsgBuffer();

    MsgErr * clone() {return new MsgErr(*this);}
};

#endif
