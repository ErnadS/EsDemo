#include "msg_unknown.h"
#include "nmea/nmea_parser.h"

MsgUnknown::MsgUnknown(QString messageType)
{
    this->m_message_type_hash   = MsgUnknown::UNKNOWNhash;
    this->m_message_type        = messageType;
}


bool MsgUnknown::setParams(QStringList)
{
    return false;
}

QString MsgUnknown::getMsgBuffer() {
    return "";
}
