#include "msg_err.h"
#include "nmea/nmea_parser.h"

MsgErr::MsgErr()
{
    this->m_message_type        = TYPE_ERR;
}

MsgErr::MsgErr(NmeaMessageErrorType error_ID)
{
    m_message_type = TYPE_ERR;
    this->m_error_id = error_ID;
}

bool MsgErr::setParams(QStringList)
{
    return false;
}

QString MsgErr::getMsgBuffer()
{
    return "";
}

