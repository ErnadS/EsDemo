#include "msg_gll.h"
#include "nmea/nmea_parser.h"

MsgGLL::MsgGLL()
{
    this->m_message_type_hash   = MsgGLL::GLLhash;
    this->m_message_type        = TYPE_GLL;
}


MsgGLL::MsgGLL(float latitude, QString northOrSouth, float longitude, QString eastOrWest, QString utcOfPosition,
               QString status, QString modeIndicator)
{
    this->m_message_type_hash   = MsgGLL::GLLhash;
    this->m_message_type        = TYPE_GLL;

    // TODO: FIX NMEA attribute
    // this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->latitude                 = latitude;
    this->northOrSouth             = northOrSouth;
    this->longitude                = longitude;
    this->eastOrWest               = eastOrWest;
    this->utcOfPosition            = utcOfPosition;
    this->status                   = status;
    this->modeIndicator            = modeIndicator;
}

bool MsgGLL::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 4){  // normal is 7
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        latitude                       = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        northOrSouth                   = m_message_parameters[1];
        longitude                      = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        eastOrWest                     = m_message_parameters[3];

        if (m_message_parameters.count() == 7) {
            utcOfPosition                  = m_message_parameters[4];
            status                         = m_message_parameters[5];
            modeIndicator                  = m_message_parameters[6];
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

QString MsgGLL::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_GLL) + "," + NmeaParser::NumberToString(latitude, 'f', 2)
            + "," + northOrSouth + "," + NmeaParser::NumberToString(longitude, 'f', 2) + "," + eastOrWest + "," +
            utcOfPosition + "," + status + "," + modeIndicator;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
