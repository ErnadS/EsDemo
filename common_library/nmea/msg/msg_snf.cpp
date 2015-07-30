#include "msg_snf.h"
#include "nmea/nmea_parser.h"

MsgSNF::MsgSNF()
{
    this->m_message_type_hash   = MsgSNF::SNFhash;
    this->m_message_type        = TYPE_SNF;
}

MsgSNF::MsgSNF(int systemID, int serialNumber, QString hardwareRev, float firmwereRev,
               float scalingForBeam1, float scalingForBeam2, float offsetTempSens,
               float scalingTempSpeed, int frequencyNr)
{
    this->m_message_type_hash   = MsgSNF::SNFhash;
    this->m_message_type        = TYPE_SNF;

    this->systemID                 = systemID;
    this->serialNumber             = serialNumber;
    this->hardwareRev              = hardwareRev;
    this->firmwereRev              = firmwereRev;
    this->scalingForBeam1          = scalingForBeam1/100;
    this->scalingForBeam2          = scalingForBeam2/100;
    this->offsetTempSens           = offsetTempSens;
    this->scalingTempSpeed         = scalingTempSpeed;
    this->frequencyNr              = frequencyNr;
}

bool MsgSNF::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 9){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        systemID                   = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        serialNumber               = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        hardwareRev                = m_message_parameters[2];
        firmwereRev                = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        firmwereRev                = firmwereRev/100;
        scalingForBeam1            = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        scalingForBeam1            = scalingForBeam1/100;
        scalingForBeam2            = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        scalingForBeam2            = scalingForBeam2/100;
        offsetTempSens             = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        scalingTempSpeed           = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        frequencyNr                = NmeaParser::StringToInt(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
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

QString MsgSNF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SNF) + ",1";
    // NOTE: !!!!!!!!
    // We are sending to sensor: $PSKPSNF,1*xx and sensor is answering with SNF message with all parameters
    /*
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SNF) + "," + QString::number(systemID)
            + "," + NmeaParser::NumberToString(serialNumber) + "," + hardwareRev + "," + NmeaParser::NumberToString((firmwereRev*100), 'f',0)
            + "," + NmeaParser::NumberToString((scalingForBeam1*100), 'f',0) + "," + NmeaParser::NumberToString((scalingForBeam2*100), 'f',0)
            + "," + NmeaParser::NumberToString(offsetTempSens, 'f',0) + "," + NmeaParser::NumberToString(scalingTempSpeed, 'f',0)
            + "," + NmeaParser::NumberToString(frequencyNr);
*/

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
