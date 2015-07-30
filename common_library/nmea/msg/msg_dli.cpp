#include "msg_dli.h"
#include "nmea/nmea_parser.h"

MsgDLI::MsgDLI()
{
    this->m_message_type_hash   = MsgDLI::DLIhash;
    this->m_message_type        = TYPE_DLI;
}

MsgDLI::MsgDLI(float total, float trip,
               int nDepthType,  // if 2 => 2 axis (forward and right), if '4' => 4 axis
               float frAxisDepthFwd_DL2, float frAxisDepthAft_DL2,
               float scAxisDepthFwd_DL2, float scAxisDepthAft_DL2, float depthAverage,
               float temperature, QString hours, QString minuts)
{
    this->m_message_type_hash   = MsgDLI::DLIhash;
    this->m_message_type        = TYPE_DLI;
    this->nDepthType            = nDepthType;
    this->total = total;
    this->trip = trip;
    this->frAxisDepthFwd_DL2 = frAxisDepthFwd_DL2;
    this->frAxisDepthAft_DL2 = frAxisDepthAft_DL2;
    this->scAxisDepthFwd_DL2 = scAxisDepthFwd_DL2;
    this->scAxisDepthAft_DL2 = scAxisDepthAft_DL2;
    this->depthAverage = depthAverage;
    this->temperature = temperature;
    this->hours = hours;
    this->minuts = minuts;
}

bool MsgDLI::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        total               = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        trip                = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        nDepthType          = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        frAxisDepthFwd_DL2  = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        frAxisDepthAft_DL2  = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        scAxisDepthFwd_DL2  = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        scAxisDepthAft_DL2  = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        depthAverage        = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        temperature         = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        hours               = m_message_parameters[9];
        minuts              = m_message_parameters[10];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 2129. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgDLI::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DLI) + ",";

    //////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(total, 'f', 2) + ",";
    msg_body += NmeaParser::NumberToString(trip, 'f', 3) + ",";
    ///////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(nDepthType) + ",";
    ///////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(frAxisDepthFwd_DL2, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(frAxisDepthAft_DL2, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(scAxisDepthFwd_DL2, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(scAxisDepthAft_DL2, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(depthAverage, 'f', 1)+ ",";
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(temperature, 'f', 1)+ ",";
    ///////////////////////////////////////////////////////////////////////////////

    msg_body += this->hours + ",";
    msg_body += this->minuts;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}

