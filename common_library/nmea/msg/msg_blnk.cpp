#include "msg_blnk.h"
#include "nmea/nmea_parser.h"

MsgBLNK::MsgBLNK()
{
    this->m_message_type_hash   = MsgBLNK::BLNKhash;
    this->m_message_type        = TYPE_BLNK;
}

MsgBLNK::MsgBLNK(int systemID, QString pingOnOff)
{
    this->m_message_type_hash   = MsgBLNK::BLNKhash;
    this->m_message_type        = TYPE_BLNK;

    this->systemID                 = systemID;
    this->pingOnOff                = pingOnOff;

    /*NmeaMessage tmpMsg;
    NmeaParser::parse(tmpMsg, (this->getMsgBuffer()));
    CopyParameters(tmpMsg);*/
}


bool MsgBLNK::setParams(QStringList m_message_parameters)
{
    // CopyParameters(nmeaMsg);
    if (m_message_parameters.count() != 3){
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

        // TODO: second parameter ????: m_message_parameters[1];
        pingOnOff                  = m_message_parameters[2];

        if((pingOnOff != "ON") && (pingOnOff != "OFF")) {
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

QString MsgBLNK::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_BLNK) + "," + NmeaParser::NumberToString(systemID)
                        + "," + pingOnOff;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
