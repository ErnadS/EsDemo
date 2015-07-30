#include "msg_alf.h"
#include "nmea/nmea_parser.h"

MsgALF::MsgALF()
{
    this->m_message_type_hash   = MsgALF::ALFhash;
    this->m_message_type        = TYPE_ALF;
}


MsgALF::MsgALF(int totalNumberOfSentences, int sentenceNumber, int sequentialMessageIdentifier, QString timeOfLastChange, QString alertCategory,
               QString alertPriority, QString alertState, QString manufacturerMnemonicCode, unsigned long alertIdentifier,
               unsigned long alertInstance, int revisionCounter, int escalationCounter, QString text)
{
    this->m_message_type_hash   = MsgALF::ALFhash;
    this->m_message_type        = TYPE_ALF;

    // TODO: FIX NMEA attribute
    //this->m_talker_id                   = SystemConfiguration::getSourceTalker();
    this->totalNumberOfSentences        = totalNumberOfSentences;
    this->sentenceNumber                = sentenceNumber;
    this->sequentialMessageIdentifier   = sequentialMessageIdentifier;
    this->timeOfLastChange              = timeOfLastChange;
    this->alertCategory                 = alertCategory;
    this->alertPriority                 = alertPriority;
    this->alertState                    = alertState;
    this->manufacturerMnemonicCode      = manufacturerMnemonicCode;
    this->alertIdentifier               = alertIdentifier;
    this->alertInstance                 = alertInstance;
    this->revisionCounter               = revisionCounter;
    this->escalationCounter             = escalationCounter;
    if(sentenceNumber == 1)
        this->alertText                 = text;
    else
        this->alertDescription          = text;
}

bool MsgALF::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 13)
    {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
    try
    {
        bool ok;

        totalNumberOfSentences              = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        sentenceNumber                      = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        sequentialMessageIdentifier         = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        timeOfLastChange                    = m_message_parameters[3];
        alertCategory                       = m_message_parameters[4];
        alertPriority                       = m_message_parameters[5];
        alertState                          = m_message_parameters[6];
        manufacturerMnemonicCode            = m_message_parameters[7];

        alertIdentifier                     = NmeaParser::StringToInt(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        alertInstance                       = NmeaParser::StringToInt(m_message_parameters[9], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        revisionCounter                     = NmeaParser::StringToInt(m_message_parameters[10], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        escalationCounter                   = NmeaParser::StringToInt(m_message_parameters[11], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        if(sentenceNumber == 1)
            this->alertText                 = m_message_parameters[12];
        else
            this->alertDescription          = m_message_parameters[13];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgALF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_ALF) + "," + NmeaParser::NumberToString(totalNumberOfSentences)
            + "," + NmeaParser::NumberToString(sentenceNumber) + "," + NmeaParser::NumberToString(sequentialMessageIdentifier)
            + "," + timeOfLastChange + "," + alertCategory + "," + alertPriority + "," + alertState + "," +
            manufacturerMnemonicCode + "," +
            NmeaParser::UintToString_FixedLength(alertIdentifier, 3) + "," +
            NmeaParser::UintToString_FixedLength(alertInstance, 0) + "," +
            NmeaParser::NumberToString(revisionCounter) + "," +
            NmeaParser::NumberToString(escalationCounter) + ",";

    if(sentenceNumber == 1)
        msg_body += alertText;
    else
        msg_body += alertDescription;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;

}
