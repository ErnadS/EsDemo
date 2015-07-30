#include "msg_dtl.h"
#include "nmea/nmea_parser.h"

MsgDTL::MsgDTL()
{
    this->m_message_type_hash   = MsgDTL::DTLhash;
    this->m_message_type        = TYPE_DTL;
}

MsgDTL::MsgDTL(float sogGPS, float stwRes_MovAvg, float sogRes_MovAvg, float stwRes_MovAvgSlewLim,
               float sogRes_MovAvgSlewLim, float stwRes_ExpFilt, float sogRes_ExpFilt)
{
    this->m_message_type_hash   = MsgDTL::DTLhash;
    this->m_message_type        = TYPE_DTL;

    this->sogGPS = sogGPS;
    this->stwRes_MovAvg = stwRes_MovAvg;
    this->sogRes_MovAvg = sogRes_MovAvg;

    this->stwRes_MovAvgSlewLim = stwRes_MovAvgSlewLim;
    this->sogRes_MovAvgSlewLim = sogRes_MovAvgSlewLim;

    this->stwRes_ExpFilt = stwRes_ExpFilt;
    this->sogRes_ExpFilt = sogRes_ExpFilt;
}

bool MsgDTL::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 7){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        sogGPS            = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        stwRes_MovAvg            = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        sogRes_MovAvg            = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        stwRes_MovAvgSlewLim            = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        sogRes_MovAvgSlewLim            = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        stwRes_ExpFilt            = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        sogRes_ExpFilt            = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 8129. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }


}

QString MsgDTL::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DTL) + ",";

    //////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(sogGPS, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(stwRes_MovAvg, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(sogRes_MovAvg, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(stwRes_MovAvgSlewLim, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(sogRes_MovAvgSlewLim, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(stwRes_ExpFilt, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(sogRes_ExpFilt, 'f', 1);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
