#include "msg_vtg.h"
#include "nmea/nmea_parser.h"

MsgVTG::MsgVTG()
{
    this->m_message_type_hash   = MsgVTG::VTGhash;
    this->m_message_type        = TYPE_VTG;
}

MsgVTG::MsgVTG(float trackDegresTrue, QString trueDegrees, float trackDegresMagnetic,
               QString magneticDegrees, float speedKnots, QString knots, float speedKilometers,
               QString kilometers, QString modeIndicator)
{
    this->m_message_type_hash   = MsgVTG::VTGhash;
    this->m_message_type        = TYPE_VTG;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                 = SystemConfiguration::getSourceTalker();
    this->trackDegresTrue          = trackDegresTrue;
    this->trueDegrees              = trueDegrees;
    this->trackDegresMagnetic      = trackDegresMagnetic;
    this->magneticDegrees          = magneticDegrees;
    this->speedKnots               = speedKnots;
    this->knots                    = knots;
    this->speedKilometers          = speedKilometers;
    this->kilometers               = kilometers;
    this->modeIndicator            = modeIndicator;
}

bool MsgVTG::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 8){  // normal is 9
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
    try
    {
        bool ok;
        trackDegresTrue                  = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        trueDegrees                      = m_message_parameters[1];
        trackDegresMagnetic              = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        magneticDegrees                  = m_message_parameters[3];
        speedKnots                       = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        knots                            = m_message_parameters[5];
        speedKilometers                  = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        kilometers                       = m_message_parameters[7];
        if (m_message_parameters.count() == 9)
            modeIndicator              = m_message_parameters[8];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgVTG::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_VTG) + "," + NmeaParser::NumberToString(trackDegresTrue, 'f', 1)
            + "," + trueDegrees + "," + NmeaParser::NumberToString(trackDegresMagnetic, 'f', 1) + "," + magneticDegrees
            + "," + NmeaParser::NumberToString(speedKnots, 'f', 1) + "," + knots + "," + NmeaParser::NumberToString(speedKilometers, 'f', 1)
            + "," + kilometers + "," + modeIndicator;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
