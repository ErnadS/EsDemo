#include "msg_cppc.h"
#include "nmea/nmea_parser.h"

MsgCPPC::MsgCPPC()
{
    this->systemAck = 1;

    this->m_message_type_hash   = MsgCPPC::CPPChash;
    this->m_message_type        = TYPE_CPPC;
}

bool MsgCPPC::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        systemAck                             = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok || systemAck != 1) {
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

QString MsgCPPC::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_CPPC) + "," + NmeaParser::NumberToString(systemAck);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
