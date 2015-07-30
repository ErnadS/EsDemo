#include "msg_idm.h"
#include "nmea/nmea_parser.h"

MsgIDM::MsgIDM()
{
    this->m_message_type_hash   = MsgIDM::IDMhash;
    this->m_message_type        = TYPE_IDM;
    this->messageVersion        = MsgIDM::msgVersion;
}

MsgIDM::MsgIDM(int commandID, QList<QString> msgParameters)
{
    this->m_message_type_hash   = MsgIDM::IDMhash;
    this->m_message_type        = TYPE_IDM;

    this->messageVersion        = MsgIDM::msgVersion;
    this->commandID             = commandID;
    this->msgParameters         = msgParameters;
}

bool MsgIDM::setParams(QStringList m_message_parameters)
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
               msgParameters.append(m_message_parameters[i]);
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

QString MsgIDM::getMsgBuffer()
{

    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_IDM) + "," +
            NmeaParser::NumberToString(messageVersion) + "," + NmeaParser::NumberToString(commandID);

    for(int i = 0; i < msgParameters.length(); i++)
        msg_body += "," + msgParameters[i];

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
