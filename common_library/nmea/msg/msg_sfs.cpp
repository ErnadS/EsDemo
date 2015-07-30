#include "msg_sfs.h"
#include "nmea/nmea_parser.h"

MsgSFS::MsgSFS()
{
    this->m_message_type_hash   = MsgSFS::SFShash;
    this->m_message_type        = TYPE_SFS;
}


MsgSFS::MsgSFS(QString simCommand, float speedLong, float speedTrans)
{
    this->m_message_type_hash   = MsgSFS::SFShash;
    this->m_message_type        = TYPE_SFS;

    this->simCommand               = simCommand;
    this->speedLong                = speedLong;
    this->speedTrans               = speedTrans;
}

bool MsgSFS::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 3){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        simCommand                 = m_message_parameters[0];
        speedLong                  = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        speedTrans                 = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
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

QString MsgSFS::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SFS) + "," +simCommand + "," +
            NmeaParser::NumberToString(speedLong, 'f', 1)+ "," +NmeaParser::NumberToString(speedTrans, 'f', 1);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
