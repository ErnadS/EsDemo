#include "msg_tst.h"
#include "nmea/nmea_parser.h"

MsgTST::MsgTST()
{
    this->m_message_type_hash   = MsgTST::TSThash;
    this->m_message_type        = TYPE_TST;
}

MsgTST::MsgTST(int systemID, int onOff, float requiredSpeed, QString formatToReturn, QString outputsEnabled)
{
    this->m_message_type_hash   = MsgTST::TSThash;
    this->m_message_type        = TYPE_TST;

    this->systemID                 = systemID;
    this->onOff                    = onOff;
    this->requiredSpeed            = requiredSpeed;
    this->formatToReturn           = formatToReturn;
    this->outputsEnabled           = outputsEnabled;
}

bool MsgTST::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 4){
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
        onOff                      = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        requiredSpeed              = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        formatToReturn             = m_message_parameters[3]; // not used. Two bytes

        outputsEnabled             = m_message_parameters[4]; // Should be 4 bytes with "0" or "1". E.g.: "0100"
        if (outputsEnabled[0] != '0' && outputsEnabled[0] != '1'){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        if (outputsEnabled[1] != '0' && outputsEnabled[1] != '1'){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        if (outputsEnabled[2] != '0' && outputsEnabled[2] != '1'){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        if (outputsEnabled[3] != '0' && outputsEnabled[3] != '1'){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;;
        return false;

    }

}

QString MsgTST::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_TST) + "," + NmeaParser::NumberToString(systemID)
             + "," + NmeaParser::NumberToString(onOff) + "," + NmeaParser::FloatToString_FixedLength_Signed(requiredSpeed, 2, 1) + "," +
            formatToReturn + ","  + outputsEnabled;// + "," ; // NOTE: the last "," is wrong but required by sensor firmware

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
