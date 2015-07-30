#include "msg_alr.h"
#include "nmea/nmea_parser.h"

MsgALR::MsgALR()
{
    this->m_message_type_hash   = MsgALR::ALRhash;
    this->m_message_type        = TYPE_ALR;
}



MsgALR::MsgALR(QString timeOfAlarm, QString uniqueAlarmNumber, QString alarmCondition, QString alarmAcknowledgeState, QString alarmDescription)
{
    this->m_message_type_hash   = MsgALR::ALRhash;
    this->m_message_type        = TYPE_ALR;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->timeOfAlarm              = timeOfAlarm;
    this->uniqueAlarmNumber        = uniqueAlarmNumber;
    this->alarmCondition           = alarmCondition;
    this->alarmAcknowledgeState    = alarmAcknowledgeState;
    this->alarmDescription         = alarmDescription;
}

bool MsgALR::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 5){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        timeOfAlarm                = m_message_parameters[0];

        uniqueAlarmNumber          = m_message_parameters[1];
        alarmCondition             = m_message_parameters[2];
        alarmAcknowledgeState      = m_message_parameters[3];
        alarmDescription           = m_message_parameters[4];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgALR::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ALR) + "," + timeOfAlarm + "," + uniqueAlarmNumber + ","+
            alarmCondition + "," + alarmAcknowledgeState + "," + alarmDescription;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
