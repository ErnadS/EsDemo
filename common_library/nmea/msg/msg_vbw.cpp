#include "msg_vbw.h"
#include "nmea/nmea_parser.h"

MsgVBW::MsgVBW()
{
    this->m_message_type_hash   = MsgVBW::VBWhash;
    this->m_message_type        = TYPE_VBW;
}

MsgVBW::MsgVBW(float longitudinalWaterSpeed, float transverseWaterSpeed, QString statusWaterSpeed,
               float longitudinalGroundSpeed, float transverseGroundSpeed, QString statusGroundSpeed,
               float sternTransWaterSpeed, QString statusSternTransWaterSpeed, float sternTransGroundSpeed,
               QString statusSternTransGroundSpeed)
{
    this->m_message_type_hash   = MsgVBW::VBWhash;
    this->m_message_type        = TYPE_VBW;
    // TODO: FIX NMEA attribute
    //this->m_number_of_decimals  = NmeaParser::getNumberOfDecimals();

    // TODO: FIX NMEA attribute
    //this->m_talker_id                   = SystemConfiguration::getSourceTalker();
    this->longitudinalWaterSpeed        = longitudinalWaterSpeed;
    this->transverseWaterSpeed          = transverseWaterSpeed;
    this->statusWaterSpeed              = statusWaterSpeed;
    this->longitudinalGroundSpeed       = longitudinalGroundSpeed;
    this->transverseGroundSpeed         = transverseGroundSpeed;
    this->statusGroundSpeed             = statusGroundSpeed;
    this->sternTransWaterSpeed          = sternTransWaterSpeed;
    this->statusSternTransWaterSpeed    = statusSternTransWaterSpeed;
    this->sternTransGroundSpeed         = sternTransGroundSpeed;
    this->statusSternTransGroundSpeed   = statusSternTransGroundSpeed;
}

bool MsgVBW::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 10){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        longitudinalWaterSpeed       = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        transverseWaterSpeed         = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        statusWaterSpeed             = m_message_parameters[2];
        longitudinalGroundSpeed      = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        transverseGroundSpeed        = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        statusGroundSpeed            = m_message_parameters[5];
        sternTransWaterSpeed         = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        statusSternTransWaterSpeed   = m_message_parameters[7];
        sternTransGroundSpeed        = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        statusSternTransGroundSpeed  = m_message_parameters[9];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number? 

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgVBW::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_VBW) + "," + NmeaParser::NumberToString(longitudinalWaterSpeed, 'f', m_number_of_decimals)+ "," +
            NmeaParser::NumberToString(transverseWaterSpeed, 'f', m_number_of_decimals) + "," + statusWaterSpeed + "," + NmeaParser::NumberToString(longitudinalGroundSpeed, 'f', m_number_of_decimals)
            + "," + NmeaParser::NumberToString(transverseGroundSpeed, 'f', m_number_of_decimals) + "," + statusGroundSpeed+ "," + NmeaParser::NumberToString(sternTransWaterSpeed, 'f', m_number_of_decimals)
            + "," + statusSternTransWaterSpeed + "," + NmeaParser::NumberToString(sternTransGroundSpeed, 'f', m_number_of_decimals) + "," +
            statusSternTransGroundSpeed;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
