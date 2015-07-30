#include "msg_rsto.h"
#include "nmea/nmea_parser.h"

MsgRSTO::MsgRSTO()
{
    this->m_message_type_hash   = MsgRSTO::RSTOhash;
    this->m_message_type        = TYPE_RSTO;
}

bool MsgRSTO::setParams(QStringList)
{
    return true;
}

QString MsgRSTO::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_RSTO) + ",";

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}

