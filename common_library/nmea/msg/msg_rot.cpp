#include "msg_rot.h"
#include "nmea/nmea_parser.h"

MsgROT::MsgROT()
{
    this->m_message_type_hash   = MsgROT::ROThash;
    this->m_message_type        = TYPE_ROT;
}

MsgROT::MsgROT(float rateOfTurn, QString status)
{
    this->m_message_type_hash   = MsgROT::ROThash;
    this->m_message_type        = TYPE_ROT;

    // TODO: FIX NMEA attribute
    //this->m_talker_id            = SystemConfiguration::getSourceTalker();
    this->rateOfTurn          = rateOfTurn;
    this->status              = status;
}

bool MsgROT::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        rateOfTurn              = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        status                = m_message_parameters[1];
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

QString MsgROT::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_ROT) + "," + NmeaParser::NumberToString(rateOfTurn, 'f', 1) + ","+ status;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;;
}
