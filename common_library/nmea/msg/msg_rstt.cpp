#include "msg_rstt.h"
#include "nmea/nmea_parser.h"


MsgRSTT::MsgRSTT()
{
    this->m_message_type_hash   = MsgRSTT::RSTThash;
    this->m_message_type        = TYPE_RSTT;
}


bool MsgRSTT::setParams(QStringList)
{
    return true;
}


QString MsgRSTT::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_RSTT) + ",";

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;

}
