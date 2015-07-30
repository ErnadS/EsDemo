#include "msg_png.h"
#include "nmea/nmea_parser.h"

MsgPNG::MsgPNG()
{
    this->m_message_type_hash   = MsgPNG::PNGhash;
    this->m_message_type        = TYPE_PNG;
}


MsgPNG::MsgPNG(int systemID)
{
    this->m_message_type_hash   = MsgPNG::PNGhash;
    this->m_message_type        = TYPE_PNG;

    this->systemID                 = systemID;
}

bool MsgPNG::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        systemID                 = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
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

QString MsgPNG::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_PNG) + "," + NmeaParser::NumberToString(systemID);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;

}
