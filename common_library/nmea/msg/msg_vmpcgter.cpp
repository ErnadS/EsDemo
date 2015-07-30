#include "msg_vmpcgter.h"
#include "nmea/nmea_parser.h"

MsgVMPCGTER::MsgVMPCGTER()
{
    this->m_message_type_hash   = MsgVMPCGTER::VMPCGTERhash;
    this->m_message_type        = TYPE_VMPCGTER;
}


MsgVMPCGTER::MsgVMPCGTER(int msgComand)
{
    this->m_message_type_hash   = MsgVMPCGTER::VMPCGTERhash;
    this->m_message_type        = TYPE_VMPCGTER;

    this->msgComand = msgComand;
}

bool MsgVMPCGTER::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        msgComand                             = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e;

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgVMPCGTER::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_VMPCGTER) + "," + NmeaParser::NumberToString(msgComand);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
