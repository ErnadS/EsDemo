#include "msg_gcf.h"

MsgGCF::MsgGCF()
{
    this->m_message_type_hash   = MsgGCF::GCFhash;
    this->m_message_type        = TYPE_GCF;
}

bool MsgGCF::setParams(QStringList)
{
   return true;
}

QString MsgGCF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_GCF) + ",";

    return (this->addCrcToMsgBuffer(msg_body));
}
