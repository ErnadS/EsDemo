#include "msg_dlm.h"
#include "nmea/nmea_parser.h"
#include <qmath.h>

MsgDLM::MsgDLM()
{
    this->m_message_type_hash   = MsgDLM::DLMhash;
    this->m_message_type        = TYPE_DLM;
}

MsgDLM::MsgDLM(float rateOfTurn, float headingTrue, float transAftSpeedToWater, float transAftSpeedToGround,
               float resCurrentSpeed, float currentDirection, int nDraftType, float gpsSog, float roll,
               float pitch, float gpsSogAngle)

{
    this->m_message_type_hash     = MsgDLM::DLMhash;
    this->m_message_type          = TYPE_DLM;

    this->rateOfTurn              = rateOfTurn;
    this->headingTrue             = headingTrue;
    this->transAftSpeedToWater    = transAftSpeedToWater;
    this->transAftSpeedToGround   = transAftSpeedToGround;
    this->resCurrentSpeed         = resCurrentSpeed;
    this->currentDirection        = currentDirection;

    if(currentDirection == std::numeric_limits<float>::max())
        this->currentDirection = std::numeric_limits<float>::max();//currentDirection; // If invalid do not multiply
    else {
        this->currentDirection = currentDirection*180/M_PI; // send degree
        if (this->currentDirection < 0)
            this->currentDirection += 360;
    }

    this->nDraftType              = nDraftType;

    this->gpsSog                  = gpsSog;

    if(roll == std::numeric_limits<float>::max())
        this->roll = roll; // If invalid do not multiply
    else
        this->roll = roll*180/M_PI; // send degree

    if(pitch == std::numeric_limits<float>::max())
        this->pitch = pitch; // If invalid do not multiply
    else
        this->pitch = pitch*180/M_PI; // send degree


    this->gpsSogAngle             = gpsSogAngle;
}

bool MsgDLM::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        rateOfTurn                    = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        headingTrue                   = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        transAftSpeedToWater          = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        transAftSpeedToGround         = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        resCurrentSpeed               = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        currentDirection              = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        nDraftType                    = NmeaParser::StringToInt(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        gpsSog                        = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        roll                          = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        pitch                         = NmeaParser::StringToFloat(m_message_parameters[9], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        gpsSogAngle                   = NmeaParser::StringToFloat(m_message_parameters[10], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 2129. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgDLM::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DLM) + ",";

    msg_body += NmeaParser::NumberToString(rateOfTurn, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(headingTrue, 'f', 1) + ",";

    msg_body += NmeaParser::NumberToString(transAftSpeedToWater, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(transAftSpeedToGround, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(resCurrentSpeed, 'f', 2)+ ",";
    msg_body += NmeaParser::NumberToString(currentDirection, 'f', 1)+ ",";
    msg_body += NmeaParser::NumberToString(nDraftType)+ ",";

    msg_body += NmeaParser::NumberToString(gpsSog, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(roll, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(pitch, 'f', 1) + ",";
    msg_body += NmeaParser::NumberToString(gpsSogAngle, 'f', 1);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
