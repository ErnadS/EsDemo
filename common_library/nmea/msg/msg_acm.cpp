#include "msg_acm.h"
#include "nmea/nmea_parser.h"

MsgACN::MsgACN()
{
    this->m_message_type_hash   = MsgACN::ACNhash;
    this->m_message_type        = TYPE_ACN;
}


MsgACN::MsgACN(QString timeOfAlert, QString manufacturerMnemonicCode, unsigned long alertIdentifier, unsigned long alertInstance,
               QString alertCommand, QString alertStatusFlag)
{
    this->m_message_type_hash   = MsgACN::ACNhash;
    this->m_message_type        = TYPE_ACN;

    // TODO: FIX NMEA attribute
    //this->m_talker_id              = SystemConfiguration::getSourceTalker();
    this->timeOfAlert              = timeOfAlert;
    this->manufacturerMnemonicCode = manufacturerMnemonicCode;
    this->alertIdentifier          = alertIdentifier;
    this->alertInstance            = alertInstance;
    this->alertCommand             = alertCommand;
    this->alertStatusFlag          = alertStatusFlag;
}

bool MsgACN::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 6)
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        timeOfAlert                = m_message_parameters[0];

        manufacturerMnemonicCode   = m_message_parameters[1];

        alertIdentifier            = NmeaParser::StringToULong(m_message_parameters[2], &ok);
        if(!ok){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        alertInstance              = NmeaParser::StringToULong(m_message_parameters[3], &ok);
        if(!ok){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        alertCommand               = m_message_parameters[4];
        alertStatusFlag            = m_message_parameters[5];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgACN::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ACN) + "," + timeOfAlert + "," + manufacturerMnemonicCode
            + ","+ NmeaParser::UlongToString_FixedLenght(alertIdentifier, 3) + "," + NmeaParser::UlongToString(alertInstance) + "," + alertCommand
             + "," + alertStatusFlag;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
