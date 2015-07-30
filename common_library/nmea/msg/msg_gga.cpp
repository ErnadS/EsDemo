#include "msg_gga.h"
#include "nmea/nmea_parser.h"

MsgGGA::MsgGGA()
{
    this->m_message_type_hash   = MsgGGA::GGAhash;
    this->m_message_type        = TYPE_GGA;
}

MsgGGA::MsgGGA(QString time, float latitude, QString northOrSouth, float longitude, QString eastOrWest,int gpsQualityIndicator,
               int nrOfSatellitesInView, float horDilPrecision, float antennaAltitude, QString unitsOfAntAlt,
               float geoidalseparation, QString unitsOfGeoidals, float ageOfGpsData, int difRefStationID)
{
    this->m_message_type_hash   = MsgGGA::GGAhash;
    this->m_message_type        = TYPE_GGA;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->time                     = time;
    this->latitude                 = latitude;
    this->northOrSouth             = northOrSouth;
    this->longitude                = longitude;
    this->eastOrWest               = eastOrWest;
    this->gpsQualityIndicator      = gpsQualityIndicator;
    this->nrOfSatellitesInView     = nrOfSatellitesInView;
    this->horDilPrecision          = horDilPrecision;
    this->antennaAltitude          = antennaAltitude;
    this->unitsOfAntAlt            = unitsOfAntAlt;
    this->geoidalseparation        = geoidalseparation;
    this->unitsOfGeoidals          = unitsOfGeoidals;
    this->ageOfGpsData             = ageOfGpsData;
    this->difRefStationID          = difRefStationID;
}

bool MsgGGA::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 12){  // should be 14
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        time                           = m_message_parameters[0];
        bool ok;
        latitude                       = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        northOrSouth                   = m_message_parameters[2];
        longitude                      = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        eastOrWest                     = m_message_parameters[4];
        gpsQualityIndicator            = NmeaParser::StringToInt(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        nrOfSatellitesInView           = NmeaParser::StringToInt(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        horDilPrecision                = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        antennaAltitude                = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        unitsOfAntAlt                  = m_message_parameters[9];
        geoidalseparation              = NmeaParser::StringToFloat(m_message_parameters[10], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        unitsOfGeoidals                = m_message_parameters[11];

        if (m_message_parameters.count() == 14) {
            ageOfGpsData                   = NmeaParser::StringToFloat(m_message_parameters[12], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            difRefStationID                = NmeaParser::StringToInt(m_message_parameters[13], &ok);
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

QString MsgGGA::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_GGA) + "," + time + "," + NmeaParser::NumberToString(latitude, 'f', 2) + "," +
            northOrSouth + "," + NmeaParser::NumberToString(longitude, 'f', 2) + "," + eastOrWest + "," +
            NmeaParser::NumberToString(gpsQualityIndicator) + "," + NmeaParser::NumberToString(nrOfSatellitesInView) + "," +
            NmeaParser::NumberToString(horDilPrecision, 'f', 1) + "," + NmeaParser::NumberToString(antennaAltitude, 'f', 1) + "," + unitsOfAntAlt
            + "," + NmeaParser::NumberToString(geoidalseparation, 'f', 1) + "," + unitsOfGeoidals + "," +
            NmeaParser::NumberToString(ageOfGpsData, 'f', 1) + "," + NmeaParser::NumberToString(difRefStationID);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
