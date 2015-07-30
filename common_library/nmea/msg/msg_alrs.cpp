#include "msg_alrs.h"
#include "nmea/nmea_parser.h"

MsgALRS::MsgALRS()
{
    this->m_message_type_hash   = MsgALRS::ALRShash;
    this->m_message_type        = TYPE_ALRS;
}


MsgALRS::MsgALRS(int nSimulatorType, QString lineOne, int statusLineOne, QString lineTwo, int statusLineTwo, QString lineThree, int statusLineThree)
{
    this->m_message_type_hash   = MsgALRS::ALRShash;
    this->m_message_type        = TYPE_ALRS;

    this->nSimulatorType           = nSimulatorType;
    this->lineOne                  = lineOne;
    this->statusLineOne            = statusLineOne;
    this->lineTwo                  = lineTwo;
    this->statusLineTwo            = statusLineTwo;
    this->lineThree                = lineThree;
    this->statusLineThree          = statusLineThree;
}

bool MsgALRS::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 7){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        nSimulatorType                      = NmeaParser::StringToInt(m_message_parameters[0], &ok);

        lineOne                        = m_message_parameters[1];
        statusLineOne                  = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        lineTwo                        = m_message_parameters[3];
        statusLineTwo                  = NmeaParser::StringToInt(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        lineThree                      = m_message_parameters[5];
        statusLineThree                = NmeaParser::StringToInt(m_message_parameters[6], &ok);
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

QString MsgALRS::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ALRS) + "," + NmeaParser::NumberToString(nSimulatorType) + "," + lineOne + "," +
            NmeaParser::NumberToString(statusLineOne) + "," + lineTwo + "," +
            NmeaParser::NumberToString(statusLineTwo) + "," + lineThree + "," +
            NmeaParser::NumberToString(statusLineThree);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
