#include "msg_ack.h"
#include "nmea/nmea_parser.h"

MsgACK::MsgACK()
{
    this->m_message_type_hash = MsgACK::ACKhash;
    this->m_message_type = TYPE_ACK;
}

MsgACK::MsgACK(int uniqueAlarmNumber)
{
    this->m_message_type_hash       = MsgACK::ACKhash;
    this->m_message_type            = TYPE_ACK;
    // TODO: FIX NMEA attribute
    //this->m_talker_id               = SystemConfiguration::getSourceTalker();
    this->uniqueAlarmNumber         = uniqueAlarmNumber;
}


bool MsgACK::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1)
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        uniqueAlarmNumber          = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgACK::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ACK) + "," + NmeaParser::NumberToString(uniqueAlarmNumber);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
