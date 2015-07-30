#include "msg_zda.h"
#include "nmea/nmea_parser.h"

MsgZDA::MsgZDA()
{
    this->m_message_type_hash   = MsgZDA::ZDAhash;
    this->m_message_type        = TYPE_ZDA;
}

MsgZDA::MsgZDA(QString time, int day, int month, int year, int localZoneHours, int LocalZoneMinutes)
{
    this->m_message_type_hash   = MsgZDA::ZDAhash;
    this->m_message_type        = TYPE_ZDA;

    // TODO: FIX NMEA attribute
    // this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->time                     = time;
    this->day                      = day;
    this->month                    = month;
    this->year                     = year;
    this->localZoneHours           = localZoneHours;
    this->LocalZoneMinutes         = LocalZoneMinutes;
}

bool MsgZDA::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 5){ // 6 is normal
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        time                           = m_message_parameters[0];
        bool ok;
        day                            = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        month                          = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        year                           = NmeaParser::StringToInt(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        localZoneHours                 = NmeaParser::StringToInt(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        if (m_message_parameters.count() == 6) {
            LocalZoneMinutes               = NmeaParser::StringToInt(m_message_parameters[5], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
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

QString MsgZDA::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ZDA) + "," + time + "," +
            NmeaParser::IntToString_FixedLength(day, 2) + "," +
            NmeaParser::IntToString_FixedLength(month, 2) + "," +
            NmeaParser::NumberToString(year) + "," +
            NmeaParser::IntToString_FixedLength(localZoneHours, 2) + "," +
            NmeaParser::IntToString_FixedLength(LocalZoneMinutes, 2);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
