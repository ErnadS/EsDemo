#include "msg_nlrt.h"

#include "nmea/nmea_parser.h"

Msg_Nlrt::Msg_Nlrt()
{

}

QString Msg_Nlrt::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TYPE_NLTT) + ",2,01000"; // Set Echo period to 1 sec.

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}

bool Msg_Nlrt::setParams(QStringList m_message_parameters) {
    Q_UNUSED(m_message_parameters);
    return false; // not implemented
}
