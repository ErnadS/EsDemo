#include "msg_alma_speed.h"
#include "nmea/nmea_parser.h"

MsgAlmaSpeed::MsgAlmaSpeed()
{
    this->m_message_type_hash   = MsgAlmaSpeed::ALMASPEEDhash;
    this->m_message_type        = TYPE_ALMA_SPEED;
}



MsgAlmaSpeed::MsgAlmaSpeed(float speedAverage)
{
    this->m_message_type_hash   = MsgAlmaSpeed::ALMASPEEDhash;
    this->m_message_type        = TYPE_ALMA_SPEED;

    this->speedAverage             = speedAverage;
    this->speedAverageWithDecimal  = speedAverage/100;
}

bool MsgAlmaSpeed::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        speedAverage               = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        speedAverageWithDecimal    = speedAverage/100;

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgAlmaSpeed::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString speedAverageString = NmeaParser::NumberToStringSigned(speedAverage, 'f', 0);

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ALMA_SPEED)
            + "," + speedAverageString;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
