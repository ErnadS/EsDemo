#include "msg_info.h"
#include "nmea/nmea_parser.h"

MsgINFO::MsgINFO()
{
    this->m_message_type_hash   = MsgINFO::INFOhash;
    this->m_message_type        = TYPE_INFO;
}

MsgINFO::MsgINFO(int systemID, QString information)
{
    this->m_message_type_hash   = MsgINFO::INFOhash;
    this->m_message_type        = TYPE_INFO;

    this->systemID              = systemID;
    this->information           = information;
}

bool MsgINFO::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
    try
    {
        bool ok;
        systemID                   = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        information              = m_message_parameters[1];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e;

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgINFO::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_INFO) + "," + NmeaParser::NumberToString(systemID)+ ","+ information;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
