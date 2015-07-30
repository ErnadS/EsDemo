#include "msg_hdt.h"
#include "nmea/nmea_parser.h"

MsgHDT::MsgHDT()
{
    this->m_message_type_hash   = MsgHDT::HDThash;
    this->m_message_type        = TYPE_HDT;
}

MsgHDT::MsgHDT(float headingDegrees, QString statusTrue)
{
    this->m_message_type_hash   = MsgHDT::HDThash;
    this->m_message_type        = TYPE_HDT;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->headingDegrees           = headingDegrees;
    this->statusTrue               = statusTrue;
}

bool MsgHDT::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        headingDegrees             = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        statusTrue                 = m_message_parameters[1];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgHDT::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_HDT) + "," + NmeaParser::NumberToString(headingDegrees, 'f', 1) + "," +
            statusTrue;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;

}
