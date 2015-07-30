#include "msg_icm.h"
#include "nmea/nmea_parser.h"

MsgICM::MsgICM()
{
    this->m_message_type_hash   = MsgICM::ICMhash;
    this->m_message_type        = TYPE_ICM;
    this->messageVersion        = MsgICM::msgVersion;
}

MsgICM::MsgICM(int commandID, QList<int> msgParameters)
{
    this->m_message_type_hash   = MsgICM::ICMhash;
    this->m_message_type        = TYPE_ICM;

    this->messageVersion        = MsgICM::msgVersion;
    this->commandID             = commandID;
    this->msgParameters         = msgParameters;
}

bool MsgICM::setParams(QStringList m_message_parameters)
{
    try
    {
        bool ok;
        messageVersion             = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        commandID                  = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        for(int i = 2; i < m_message_parameters.length(); i++)
            {
                int tmpParameter   = NmeaParser::StringToInt(m_message_parameters[i], &ok);
                if(!ok) {
                    m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                    return false;
                }
                else
                    msgParameters.append(tmpParameter);
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

QString MsgICM::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ICM) + "," +
            NmeaParser::NumberToString(messageVersion) + "," + NmeaParser::NumberToString(commandID);

    for(int i = 0; i < msgParameters.length(); i++)
        msg_body += "," + NmeaParser::NumberToString(msgParameters[i]);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
