#include "msg_vlw.h"
#include "nmea/nmea_parser.h"

MsgVLW::MsgVLW()
{
    this->m_message_type_hash   = MsgVLW::VLWhash;
    this->m_message_type        = TYPE_VLW;
}

MsgVLW::MsgVLW(float totCumulativeWaterDist, QString totCumulativeWaterDistUnit, float waterDistSinceReset,
               QString waterDistSinceResetUnit, float totCumulativeGroundDist, QString totCumulativeGroundDistUnit,
               float groundDistSinceReset, QString groundDistSinceResetUnit)
{
    this->m_message_type_hash   = MsgVLW::VLWhash;
    this->m_message_type        = TYPE_VLW;
    // TODO: FIX NMEA attribute
    // this->m_number_of_decimals  = NmeaParser::getNumberOfDecimals();

    // TODO: FIX NMEA attribute
    //this->m_talker_id                    = SystemConfiguration::getSourceTalker();
    this->totCumulativeWaterDist         = totCumulativeWaterDist;
    this->totCumulativeWaterDistUnit     = totCumulativeWaterDistUnit;
    this->waterDistSinceReset            = waterDistSinceReset;
    this->waterDistSinceResetUnit        = waterDistSinceResetUnit;
    this->totCumulativeGroundDist        = totCumulativeGroundDist;
    this->totCumulativeGroundDistUnit    = totCumulativeGroundDistUnit;
    this->groundDistSinceReset           = groundDistSinceReset;
    this->groundDistSinceResetUnit       = groundDistSinceResetUnit;
}

bool MsgVLW::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 8){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        totCumulativeWaterDist           = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        totCumulativeWaterDistUnit       = m_message_parameters[1];
        waterDistSinceReset              = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        waterDistSinceResetUnit          = m_message_parameters[3];
        totCumulativeGroundDist          = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        totCumulativeGroundDistUnit      = m_message_parameters[5];
        groundDistSinceReset              = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        groundDistSinceResetUnit          = m_message_parameters[7];


        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgVLW::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_VLW) + "," + NmeaParser::NumberToString(totCumulativeWaterDist, 'f', m_number_of_decimals)+ "," +
            totCumulativeWaterDistUnit + "," + NmeaParser::NumberToString(waterDistSinceReset, 'f', m_number_of_decimals) + "," + waterDistSinceResetUnit
             + "," + NmeaParser::NumberToString(totCumulativeGroundDist, 'f',m_number_of_decimals) + "," + totCumulativeGroundDistUnit + "," +
            NmeaParser::NumberToString(groundDistSinceReset, 'f', m_number_of_decimals) + "," + groundDistSinceResetUnit;


    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
