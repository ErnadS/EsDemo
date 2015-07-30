#include "msg_mtwf.h"
#include "nmea/nmea_parser.h"

MsgMTWF::MsgMTWF()
{
    this->m_message_type_hash   = MsgMTWF::MTWFhash;
    this->m_message_type        = TYPE_MTWF;
}

MsgMTWF::MsgMTWF(float temperature, QString centigrade)
{
    this->m_message_type_hash   = MsgMTWF::MTWFhash;
    this->m_message_type        = TYPE_MTWF;

    this->temperature              = temperature;
    this->centigrade               = centigrade;
}

bool MsgMTWF::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        temperature                = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        centigrade                 = m_message_parameters[1];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgMTWF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_MTWF)
            + "," + NmeaParser::NumberToString(temperature, 'f', 1) + "," + centigrade;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
