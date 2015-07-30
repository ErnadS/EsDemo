#include "msg_alma_temp.h"
#include "nmea/nmea_parser.h"

MsgAlmaTemp::MsgAlmaTemp()
{
    this->m_message_type_hash   = MsgAlmaTemp::ALMASTEMPhash;
    this->m_message_type        = TYPE_ALMA_TEMP;
}



MsgAlmaTemp::MsgAlmaTemp(float tempereture)
{
    this->m_message_type_hash   = MsgAlmaTemp::ALMASTEMPhash;
    this->m_message_type        = TYPE_ALMA_TEMP;

    this->tempereture               = tempereture;
    this->temperatureWithDecimal    = tempereture/10;
}

bool MsgAlmaTemp::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;

        tempereture                = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        temperatureWithDecimal     = tempereture/10;

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }

}

QString MsgAlmaTemp::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString temperatureString = NmeaParser::NumberToStringSigned(tempereture, 'f', 0);

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ALMA_TEMP)
            + "," + temperatureString;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;

}
