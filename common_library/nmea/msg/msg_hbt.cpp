#include "msg_hbt.h"
#include "nmea/nmea_parser.h"

MsgHBT::MsgHBT()
{
    // TODO: FIX NMEA attribute
    //this->m_talker_id = SystemConfiguration::getSourceTalker();
    this->m_message_type_hash   = MsgHBT::HBThash;
    this->m_message_type        = TYPE_HBT;
}

MsgHBT::MsgHBT(int nHeartBeatPeriod, QString strValid, int nHeartBeatCounter)
{
    this->m_message_type_hash   = MsgHBT::HBThash;
    this->m_message_type        = TYPE_HBT;
    // TODO: FIX NMEA attribute
    // this->m_talker_id = SystemConfiguration::getSourceTalker();
    this->nHeartBeatPeriod = nHeartBeatPeriod; // e.g. 60 => sent each 60 seconds
    this->strValid = strValid;  // "A" or "V"
    this->nHeartBeatCounter = nHeartBeatCounter;
}

bool MsgHBT::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 3){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        nHeartBeatPeriod           = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        strValid                   = m_message_parameters[1];
        if (strValid != "A" && strValid != "V")
        {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        nHeartBeatCounter          = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 861. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgHBT::getMsgBuffer()
{
    QString msg_body= QString(m_talker_id) + QString(TYPE_HBT) + "," + QString::number(nHeartBeatPeriod) + "," +
            strValid  + "," + QString::number(nHeartBeatCounter);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
