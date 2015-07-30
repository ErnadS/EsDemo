#include "msg_ver.h"
#include "nmea/nmea_parser.h"

MsgVER::MsgVER()
{
    this->m_message_type_hash   = MsgVER::VERhash;
    this->m_message_type        = TYPE_VER;
}

MsgVER::MsgVER(int totalNumberOfSentences, int sentenceNumber, QString deviceType, QString venderID,
               QString uniqueIdentifier, QString manufacturerSerialNumber, QString modelCode,
               QString softwareRevision, QString hardwareRevision, int sequentialMessageIdentifier)
{
    this->m_message_type_hash         = MsgVER::VERhash;
    this->m_message_type              = TYPE_VER;

    this->totalNumberOfSentences      = totalNumberOfSentences;
    this->sentenceNumber              = sentenceNumber;
    this->deviceType                  = deviceType;
    this->venderID                    = venderID;
    this->uniqueIdentifier            = uniqueIdentifier;
    this->manufacturerSerialNumber    = manufacturerSerialNumber;
    this->modelCode                   = modelCode;
    this->softwareRevision            = softwareRevision;
    this->hardwareRevision            = hardwareRevision;
    this->sequentialMessageIdentifier = sequentialMessageIdentifier;
}

bool MsgVER::setParams(QStringList m_message_parameters)
{
    if ((m_message_parameters.count() != 10) && (m_message_parameters.count() != 0)){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    if(m_message_parameters.count() == 0)
    {
        uniqueIdentifier = "Request";
        return true;
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

        deviceType                          = m_message_parameters[2];
        venderID                            = m_message_parameters[3];
        uniqueIdentifier                    = m_message_parameters[4];
        manufacturerSerialNumber            = m_message_parameters[5];
        modelCode                           = m_message_parameters[6];
        softwareRevision                    = m_message_parameters[7];
        hardwareRevision                    = m_message_parameters[8];

        sequentialMessageIdentifier         = NmeaParser::StringToInt(m_message_parameters[9], &ok);
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

QString MsgVER::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    this->totalNumberOfSentences      = totalNumberOfSentences;
    this->sentenceNumber              = sentenceNumber;
    this->deviceType                  = deviceType;
    this->venderID                    = venderID;
    this->uniqueIdentifier            = uniqueIdentifier;
    this->manufacturerSerialNumber    = manufacturerSerialNumber;
    this->modelCode                   = modelCode;
    this->softwareRevision            = softwareRevision;
    this->hardwareRevision            = hardwareRevision;
    this->sequentialMessageIdentifier = sequentialMessageIdentifier;
    QString msg_body = QString(TALKER_SKIPPER) + QString(TYPE_VER)
            + "," + NmeaParser::NumberToString(totalNumberOfSentences)
            + "," + NmeaParser::NumberToString(sentenceNumber)+ "," + deviceType
            + "," + venderID + "," + uniqueIdentifier + "," + manufacturerSerialNumber
            + "," + modelCode + "," + softwareRevision + "," + hardwareRevision
            + "," + NmeaParser::NumberToString(sequentialMessageIdentifier);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
