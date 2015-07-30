#include "msg_dlr.h"
#include "nmea/nmea_parser.h"
#include <qmath.h>

MsgDLR::MsgDLR()
{
    this->m_message_type_hash   = MsgDLR::DLRhash;
    this->m_message_type        = TYPE_DLR;
}

MsgDLR::MsgDLR(float longSpeedToWater_DL2, float transSpeedToWater_DL2, float resSpeedToWater_DL2,
                float longSpeedToGround_DL2, float transSpeedToGround_DL2,
               float resSpeedToGround_DL2, float speedToWater_DL1,
               bool bUsedGPS, bool bWC_fromGPS)
{
    this->m_message_type_hash   = MsgDLR::DLRhash;
    this->m_message_type        = TYPE_DLR;

    this->longSpeedToWater_DL2  = longSpeedToWater_DL2;
    this->transSpeedToWater_DL2 = transSpeedToWater_DL2;
    this->resSpeedToWater_DL2   = resSpeedToWater_DL2;


    if(longSpeedToWater_DL2 != std::numeric_limits<float>::max() && transSpeedToWater_DL2 != std::numeric_limits<float>::max()) {
        this->speedToWater_DL2_Direction = (qAtan2(transSpeedToWater_DL2, longSpeedToWater_DL2))*180/M_PI;
        if (this->speedToWater_DL2_Direction < 0)
            this->speedToWater_DL2_Direction += 360;
    } else {
        this->speedToWater_DL2_Direction = std::numeric_limits<float>::max();
    }

    this->longSpeedToGround_DL2 = longSpeedToGround_DL2;
    this->transSpeedToGround_DL2 = transSpeedToGround_DL2;
    this->resSpeedToGround_DL2 = resSpeedToGround_DL2;


    if(longSpeedToGround_DL2 != std::numeric_limits<float>::max() && transSpeedToGround_DL2 != std::numeric_limits<float>::max()) {
        this->speedToGround_DL2_Direction = (qAtan2(transSpeedToGround_DL2, longSpeedToGround_DL2))*180/M_PI;
        if (this->speedToGround_DL2_Direction < 0)
            this->speedToGround_DL2_Direction += 360;
    } else {
        this->speedToGround_DL2_Direction = std::numeric_limits<float>::max();
    }

    this->speedToWater_DL1 = speedToWater_DL1;

    this->bUsedGPS = bUsedGPS;
    this->bWC_fromGPS = bWC_fromGPS;
}

bool MsgDLR::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        longSpeedToWater_DL2            = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        transSpeedToWater_DL2           = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        resSpeedToWater_DL2             = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        speedToWater_DL2_Direction      = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        longSpeedToGround_DL2           = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        transSpeedToGround_DL2          = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        resSpeedToGround_DL2            = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        speedToGround_DL2_Direction     = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        speedToWater_DL1                = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        if (m_message_parameters[9] == "1")
            bUsedGPS = true;
        else if (m_message_parameters[9] == "0")
            bUsedGPS = false;
        else {
            ok = false; // Error
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        }

        if (m_message_parameters[10] == "1")
            bWC_fromGPS = true;
        else if (m_message_parameters[10] == "0")
            bWC_fromGPS = false;
        else {
            ok = false; // Error
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
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

QString MsgDLR::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DLR) + ",";

    //////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(longSpeedToWater_DL2, 'f', 2) + ",";
    msg_body += NmeaParser::NumberToString(transSpeedToWater_DL2, 'f', 2) + ",";
    msg_body += NmeaParser::NumberToString(resSpeedToWater_DL2, 'f', 2) + ",";
    msg_body += NmeaParser::NumberToString(speedToWater_DL2_Direction, 'f', 1) + ",";
    ///////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(longSpeedToGround_DL2, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(transSpeedToGround_DL2, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(resSpeedToGround_DL2, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(speedToGround_DL2_Direction, 'f', 1)+ ",";
    ///////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(speedToWater_DL1, 'f', 1)+ ",";
    ///////////////////////////////////////////////////////////////////////////////

    if (this->bUsedGPS) {
        msg_body += "1,";
    } else {
        msg_body += "0,";
    }

    if (this->bWC_fromGPS) {
        msg_body += "1";
    } else {
        msg_body += "0";
    }

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
