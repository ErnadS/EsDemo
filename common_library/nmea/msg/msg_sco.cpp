#include "msgsco.h"

MsgSCO::MsgSCO()
{
    this->m_message_type_hash   = MsgSCO::SCOhash;
    this->m_message_type        = TYPE_SCO;
}

MsgSCO::MsgSCO(QString sourceMacAddres, QString setupType)
{
    this->m_message_type_hash   = MsgSCO::SCOhash;
    this->m_message_type        = TYPE_SCO;

    this->sourceMacAddres       = sourceMacAddres;
    this->setupType             = setupType;
}

bool MsgSCO::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        error_ID = ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        sourceMacAddres                     = m_message_parameters[0];
        setupType                           = m_message_parameters[1];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        error_ID = ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgSCO::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SCO) + "," + sourceMacAddres
            + "," + setupType;

    return (this->addCrcToMsgBuffer(msg_body));
}
