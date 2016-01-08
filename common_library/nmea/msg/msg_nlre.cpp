#include "msg_nlre.h"

#include "nmea/nmea_parser.h"

Msg_Nlre::Msg_Nlre()
{
    this->m_message_type_hash   = Msg_Nlre::NLREhash;
    this->m_message_type        = TYPE_NLRE;
}

QString Msg_Nlre::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TYPE_NLRE) + ",2,00000"; // start Echo

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}

bool Msg_Nlre::setParams(QStringList m_message_parameters) {
    Q_UNUSED(m_message_parameters);
    return false; // not implemented
}
