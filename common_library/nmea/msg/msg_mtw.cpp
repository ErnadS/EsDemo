#include "msg_mtw.h"
#include "nmea/nmea_parser.h"

MsgMTW::MsgMTW()
{
    this->m_message_type_hash   = MsgMTW::MTWhash;
    this->m_message_type        = TYPE_MTW;
}

MsgMTW::MsgMTW(float waterTemperature, QString unitOfMeasurement)
{
    this->m_message_type_hash   = MsgMTW::MTWhash;
    this->m_message_type        = TYPE_MTW;

    // TODO: FIX NMEA attribtue
    // this->m_talker_id = SystemConfiguration::getSourceTalker();
    this->waterTemperature    = waterTemperature;
    this->unitOfMeasurement   = unitOfMeasurement;
}

bool MsgMTW::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        waterTemperature           = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        unitOfMeasurement          = m_message_parameters[1];


        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number? 

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgMTW::getMsgBuffer()
{   
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_MTW) + "," + NmeaParser::NumberToString(waterTemperature, 'f', 1) + ","+ unitOfMeasurement;


    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
