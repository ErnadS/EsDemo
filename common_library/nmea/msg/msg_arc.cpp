#include "msg_arc.h"
#include "nmea/nmea_parser.h"

MsgARC::MsgARC()
{
    this->m_message_type_hash   = MsgARC::ARChash;
    this->m_message_type        = TYPE_ARC;
}

MsgARC::MsgARC(QString releaseTime, int manufacturerMnemonicCode, unsigned long alertIdentifier,
               unsigned long alertInstance, QString refusedAlertCommand)
{
    this->m_message_type_hash   = MsgARC::ARChash;
    this->m_message_type        = TYPE_ARC;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                      = SystemConfiguration::getSourceTalker();
    this->releaseTime                   = releaseTime;
    this->manufacturerMnemonicCode      = manufacturerMnemonicCode;
    this->alertIdentifier               = alertIdentifier;
    this->alertInstance                 = alertInstance;
    this->refusedAlertCommand           = refusedAlertCommand;
}

bool MsgARC::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 5){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
    try
    {
        bool ok;
        releaseTime                         = m_message_parameters[0];
        manufacturerMnemonicCode            = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        alertIdentifier                     = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        alertInstance                       = NmeaParser::StringToInt(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        refusedAlertCommand                 = m_message_parameters[4];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgARC::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ARC) + "," + releaseTime + "," +
            NmeaParser::NumberToString(manufacturerMnemonicCode) + "," +
            NmeaParser::UintToString_FixedLength(alertIdentifier, 3) + "," +
            NmeaParser::UintToString_FixedLength(alertInstance, 0) + "," + refusedAlertCommand;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
