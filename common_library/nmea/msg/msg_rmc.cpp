#include "msg_rmc.h"
#include "nmea/nmea_parser.h"

MsgRMC::MsgRMC()
{
    this->m_message_type_hash   = MsgRMC::RMChash;
    this->m_message_type        = TYPE_RMC;
}

MsgRMC::MsgRMC(QString time, QString status, float latitude, QString northOrSouth, float longitude, QString eastOrWest,
               float speedOverGround, float courseOverGround, QString date, float magneticVariation,
               QString magVarEastOrWest, QString modeIndicator, QString navigationalStatus)
{
    this->m_message_type_hash   = MsgRMC::RMChash;
    this->m_message_type        = TYPE_RMC;

    // TODO: FIX NMEA attribute
    // this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->time                     = time;
    this->status                   = status;
    this->latitude                 = latitude;
    this->northOrSouth             = northOrSouth;
    this->longitude                = longitude;
    this->eastOrWest               = eastOrWest;
    this->speedOverGround          = speedOverGround;
    this->courseOverGround         = courseOverGround;
    this->date                     = date;
    this->magneticVariation        = magneticVariation;
    this->magVarEastOrWest         = magVarEastOrWest;
    this->modeIndicator            = modeIndicator;
    this->navigationalStatus       = navigationalStatus;
}

bool MsgRMC::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        time                           = m_message_parameters[0];
        status                         = m_message_parameters[1];
        bool ok;
        latitude                       = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        northOrSouth                   = m_message_parameters[3];
        longitude                      = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        eastOrWest                     = m_message_parameters[5];
        speedOverGround                = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        courseOverGround               = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        date                           = m_message_parameters[8];
        magneticVariation              = NmeaParser::StringToFloat(m_message_parameters[9], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        magVarEastOrWest               = m_message_parameters[10];

        if (m_message_parameters.count() == 13) {
            modeIndicator                  = m_message_parameters[11];
            navigationalStatus             = m_message_parameters[12];
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

QString MsgRMC::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_RMC) + "," + time + "," +  status + "," +
            NmeaParser::NumberToString(latitude, 'f', 2) + "," + northOrSouth + "," +
            NmeaParser::NumberToString(longitude, 'f', 2) + "," + eastOrWest + "," +
            NmeaParser::NumberToString(speedOverGround, 'f', 1) + "," +
            NmeaParser::NumberToString(courseOverGround, 'f', 1) + "," + date + "," +
            NmeaParser::NumberToString(magneticVariation, 'f', 1) + "," + magVarEastOrWest+ "," + modeIndicator
            + "," + navigationalStatus ;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
