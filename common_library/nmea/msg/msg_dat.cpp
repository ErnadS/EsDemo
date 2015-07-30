#include "msg_dat.h"
#include "nmea/nmea_parser.h"

MsgDAT::MsgDAT()
{
    this->m_message_type_hash   = MsgDAT::DAThash;
    this->m_message_type        = TYPE_DAT;
}


MsgDAT::MsgDAT(int systemID, float frAxisFwdSpeed, int frAxisFwdSigQuality, float frAxisAftSpeed, int frAxisAftSigQuality,
               float fTemperature, int tiltX, int tiltY, int tiltZ, float scAxisFwdSpeed, int scAxisFwdSigQuality,
               float scAxisAftSpeed, int scAxisAftSigQuality, float depthFwd, float depthAft) //: NmeaMessage()
{
    this->m_message_type_hash   = MsgDAT::DAThash;
    this->m_message_type        = TYPE_DAT;

    this->systemID              = systemID;
    this->fwdSpeedWater        = frAxisFwdSpeed;
    this->fwdSigQualityWater   = frAxisFwdSigQuality;
    this->aftSpeedWater        = frAxisAftSpeed;
    this->aftSigQualityWater   = frAxisAftSigQuality;
    this->fTemperature          = fTemperature;
    this->tiltX                 = tiltX;
    this->tiltY                 = tiltY;
    this->tiltZ                 = tiltZ;
    this->fwdSpeedGround        = scAxisFwdSpeed;
    this->fwdSigQualityGround   = scAxisFwdSigQuality;
    this->aftSpeedGround        = scAxisAftSpeed;
    this->aftSigQualityGround   = scAxisAftSigQuality;
    this->depthFwd              = depthFwd;
    this->depthAft              = depthAft;
}


#define MAX_BOAT_SPEED   70
#define MIN_BOAT_SPEED   -70



// received DAT message. Parse and set parameters (member variables)
bool MsgDAT::setParams(QStringList m_message_parameters) {

    if(m_message_parameters[0] == "2" || m_message_parameters[0] == "3" || m_message_parameters[0] == "4")
    {
        int nPos;

        if (m_message_parameters.count() != 15){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        try
        {
            bool ok;
            systemID = NmeaParser::StringToInt(m_message_parameters[0], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSigQualityWater  = NmeaParser::StringToInt(m_message_parameters[2], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSigQualityWater     = NmeaParser::StringToInt(m_message_parameters[4], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            fTemperature               = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
            if (!ok) {
                 m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                 return false;
            }
            // NOTE: Tilt is not used yet. We are receiving:  XXX,YYY,ZZZ from the real sensor (not a numbers)
            tiltX                      = NmeaParser::StringToInt(m_message_parameters[6], &ok);
            if(!ok) return false;
            tiltY                      = NmeaParser::StringToInt(m_message_parameters[7], &ok);
            if(!ok) return false;
            tiltZ                      = NmeaParser::StringToInt(m_message_parameters[8], &ok);
            if(!ok) return false;

            nPos = 9;

            fwdSpeedGround             = NmeaParser::StringToFloat(m_message_parameters[nPos++], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            fwdSigQualityGround      = NmeaParser::StringToInt(m_message_parameters[nPos++], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSpeedGround             = NmeaParser::StringToFloat(m_message_parameters[nPos++], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            aftSigQualityGround       = NmeaParser::StringToInt(m_message_parameters[nPos++], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            // TODO: REMOVE THIS TEST/SIMULATION
            depthFwd                   = NmeaParser::StringToFloat(m_message_parameters[nPos++], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            depthAft                   =  NmeaParser::StringToFloat(m_message_parameters[nPos++], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            return true;
        }
        catch (int e)
        {
            qDebug() << "Error 832. Exception: " << e;

            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;

        }
    } else if(m_message_parameters[0] == "1")
    {
      /* if (m_message_parameters.count() != 15){
            error_ID = ERR_NMEA_FORMAT;
            return false;
        }*/
        try
        {
            bool ok;
            systemID                   = NmeaParser::StringToInt(m_message_parameters[0], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSigQualityWater         = NmeaParser::StringToInt(m_message_parameters[2], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSigQualityWater         = NmeaParser::StringToInt(m_message_parameters[4], &ok);
            if(!ok)  {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            fTemperature               = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
            if (!ok) {
                 m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                 return false;
            }
            // NOTE: Tilt is not used yet. We are receiving:  XXX,YYY,ZZZ from the real sensor (not a numbers)
            tiltX                      = 0; //NmeaParser::StringToInt(nmeaMsg.m_message_parameters[6], &ok);
            //if(!ok) return false;
            tiltY                      = 0; //NmeaParser::StringToInt(nmeaMsg.m_message_parameters[7], &ok);
            //if(!ok) return false;
            tiltZ                      = 0; // NmeaParser::StringToInt(m_message_parameters[8], &ok);
            //if(!ok) return false;
            fwdSpeedGround             =  0;
            fwdSigQualityGround        =  8;
            aftSpeedGround             = 0;
            aftSigQualityGround        = 8;
            depthFwd                   = 0;
            depthAft                   = 0;

            return true;
        }
        catch (int e)
        {
            qDebug() << "Error 834. Exception: " << e;

            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
    }

    try
    {
        if(m_message_parameters[0].toUInt()==1)
        {
            if (m_message_parameters.count() != 6){
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            bool ok;
            systemID                   = NmeaParser::StringToInt(m_message_parameters[0], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
            if(!ok || fwdSpeedWater > 70 || fwdSpeedWater < -70) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            fwdSigQualityWater         = NmeaParser::StringToInt(m_message_parameters[2], &ok);
            if(!ok || fwdSigQualityWater < 0 || fwdSigQualityWater > 10) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSpeedWater              = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
            if(!ok || aftSpeedWater > 70 || aftSpeedWater < 70) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
            aftSigQualityWater         = NmeaParser::StringToInt(m_message_parameters[4], &ok);
            if(!ok || fwdSpeedWater > 70 || fwdSpeedWater < -70) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            fTemperature               = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }

            tiltX                    = 0;
            tiltY                    = 0;
            tiltZ                    = 0;

            return true;
        }

    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e;

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }

    m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
    return false;
}

QString MsgDAT::getMsgBuffer() {
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DAT) + "," + NmeaParser::NumberToString(systemID)+ ",";

    // frAxisFwdSpeed = frAxisFwdSpeed.Replace(',', '.');  // if wrong regional settings, text is with ","
    // for all float variables


    msg_body = msg_body + NmeaParser::NumberToStringSigned(fwdSpeedWater, 'f', 1);
    msg_body = msg_body + "," + NmeaParser::NumberToString(fwdSigQualityWater)+ ",";
    msg_body = msg_body + NmeaParser::NumberToStringSigned(aftSpeedWater, 'f', 1);
    msg_body = msg_body + "," + NmeaParser::NumberToString(aftSigQualityWater)+ ",";
    msg_body = msg_body + NmeaParser::NumberToStringSigned(fTemperature, 'f', 1);

    if(systemID==1)
        return (this->addCrcToMsgBuffer(msg_body));

    msg_body = msg_body + ",";
    msg_body = msg_body + NmeaParser::NumberToString(tiltX) + "," + NmeaParser::NumberToString(tiltY) + "," +
            NmeaParser::NumberToString(tiltZ) + ",";

    msg_body = msg_body + NmeaParser::NumberToStringSigned(fwdSpeedGround, 'f', 1);
    msg_body = msg_body + "," + NmeaParser::NumberToString(fwdSigQualityGround)+ ",";
    msg_body = msg_body + NmeaParser::NumberToStringSigned(aftSpeedGround, 'f', 1);
    msg_body = msg_body + "," + NmeaParser::NumberToString(aftSigQualityGround)+ ",";
    msg_body = msg_body + NmeaParser::NumberToString(depthFwd) + "," + NmeaParser::NumberToString(depthAft);


    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
