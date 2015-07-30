#include "msg_ztg.h"
#include "nmea/nmea_parser.h"

MsgZTG::MsgZTG()
{
    this->m_message_type_hash   = MsgZTG::ZTGhash;
    this->m_message_type        = TYPE_ZTG;
}

MsgZTG::MsgZTG(QString time, QString timeToGo, QString destinationWaypointID)
{
    this->m_message_type_hash   = MsgZTG::ZTGhash;
    this->m_message_type        = TYPE_ZTG;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->time                     = time;
    this->timeToGo                 = timeToGo;
    this->destinationWaypointID    = destinationWaypointID;
}

bool MsgZTG::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 3){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        time                           = m_message_parameters[0];
        timeToGo                       = m_message_parameters[1];
        destinationWaypointID          = m_message_parameters[2];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgZTG::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ZTG) + "," + time + "," +
            timeToGo + "," + destinationWaypointID ;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
