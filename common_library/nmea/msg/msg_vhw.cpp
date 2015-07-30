#include "msg_vhw.h"
#include "nmea/nmea_parser.h"

MsgVHW::MsgVHW()
{
    this->m_message_type_hash   = MsgVHW::VHWhash;
    this->m_message_type        = TYPE_VHW;
}

MsgVHW::MsgVHW(float degressTrue, QString typeDegressOne, float degressMagnetic, QString typeDegressTwo, float speedKnots,
               QString unitSpeedOne, float speedKilometers, QString unitSpeedTwo)
{
    this->m_message_type_hash   = MsgVHW::VHWhash;
    this->m_message_type        = TYPE_VHW;
    // TODO: FIX NMEA attribute
    //this->m_number_of_decimals  = NmeaParser::getNumberOfDecimals();

    // TODO: FIX NMEA attribute
    //this->m_talker_id            = SystemConfiguration::getSourceTalker();
    this->degressTrue            = degressTrue;
    this->typeDegressOne         = typeDegressOne;
    this->degressMagnetic        = degressMagnetic;
    this->typeDegressTwo         = typeDegressTwo;
    this->speedKnots             = speedKnots;
    this->unitSpeedOne           = unitSpeedOne;
    this->speedKilometers        = speedKilometers;
    this->unitSpeedTwo           = unitSpeedTwo;

  if (speedKilometers > 10000)
      speedKilometers = 100;
}

bool MsgVHW::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 8){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        degressTrue                = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        typeDegressOne             = m_message_parameters[1];
        degressMagnetic            = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        typeDegressTwo             = m_message_parameters[3];
        speedKnots                 = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        unitSpeedOne               = m_message_parameters[5];
        speedKilometers            = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        unitSpeedTwo               = m_message_parameters[7];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgVHW::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(m_talker_id) + QString(TYPE_VHW) + "," + NmeaParser::NumberToString(degressTrue, 'f', 1)+ "," + typeDegressOne + "," +
            NmeaParser::NumberToString(degressMagnetic, 'f', 1) + "," + typeDegressTwo + "," + NmeaParser::NumberToString(speedKnots, 'f', m_number_of_decimals) + "," + unitSpeedOne
            + "," + NmeaParser::NumberToString(speedKilometers, 'f', m_number_of_decimals) + "," +unitSpeedTwo;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
