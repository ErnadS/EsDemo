#include "msg_dpt.h"
#include "nmea/nmea_parser.h"

MsgDPT::MsgDPT()
{
    this->m_message_type_hash   = MsgDPT::DPThash;
    this->m_message_type        = TYPE_DPT;
}


MsgDPT::MsgDPT(float waterDepth, float transducerOffset, float maximumDepth)
{

    this->m_message_type_hash   = MsgDPT::DPThash;
    this->m_message_type        = TYPE_DPT;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->waterDepth               = waterDepth;
    this->transducerOffset         = transducerOffset;
    this->maximumDepth             = maximumDepth;
}

bool MsgDPT::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 3){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        waterDepth                 = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        transducerOffset           = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        maximumDepth               = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
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

QString MsgDPT::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= "II" + QString(TYPE_DPT) + "," + NmeaParser::NumberToString(waterDepth, 'f', 2) + "," +
            NmeaParser::NumberToString(transducerOffset, 'f', 2) + "," + NmeaParser::NumberToString(maximumDepth, 'f', 2);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
