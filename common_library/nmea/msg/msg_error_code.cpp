#include "msg_error_code.h"
#include "nmea/nmea_parser.h"

MsgERRORCODE::MsgERRORCODE()
{
    this->m_message_type_hash   = MsgERRORCODE::ERRORCODEhash;
    this->m_message_type        = TYPE_ERRORCODE;
}

MsgERRORCODE::MsgERRORCODE(unsigned errorCode, unsigned errorCount)
{
    this->m_message_type_hash   = MsgERRORCODE::ERRORCODEhash;
    this->m_message_type        = TYPE_ERRORCODE;

    this->errorCode = errorCode;
    this->errorCount = errorCount;
}

bool MsgERRORCODE::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        errorCode                             = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        errorCount                            = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
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

QString MsgERRORCODE::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ERRORCODE) + "," + NmeaParser::NumberToString(errorCode) + "," +
            NmeaParser::NumberToString(errorCount);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
