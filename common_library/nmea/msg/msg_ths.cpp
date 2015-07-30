#include "msg_ths.h"
#include "nmea/nmea_parser.h"

MsgTHS::MsgTHS()
{
    this->m_message_type_hash   = MsgTHS::THShash;
    this->m_message_type        = TYPE_THS;
}

MsgTHS::MsgTHS(float headingDegrees, QString modeIndicator)
{
    this->m_message_type_hash   = MsgTHS::THShash;
    this->m_message_type        = TYPE_THS;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->headingDegrees           = headingDegrees;
    this->modeIndicator            = modeIndicator;
}

bool MsgTHS::setParams(QStringList m_message_parameters)
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
        modeIndicator              = m_message_parameters[1];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }

}

QString MsgTHS::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_THS) + "," + NmeaParser::NumberToString(headingDegrees, 'f', 1) + "," +
            modeIndicator;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
