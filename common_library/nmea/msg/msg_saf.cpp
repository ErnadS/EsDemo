#include "msg_saf.h"
#include "nmea/nmea_parser.h"

MsgSAF::MsgSAF()
{
    this->m_message_type_hash   = MsgSAF::SAFhash;
    this->m_message_type        = TYPE_SAF;
}

MsgSAF::MsgSAF(int outputFrom)
{
    this->m_message_type_hash   = MsgSAF::SAFhash;
    this->m_message_type        = TYPE_SAF;

    this->outputFrom        = outputFrom;
}

bool MsgSAF::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 1){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;

        outputFrom                         = NmeaParser::StringToInt(m_message_parameters[0], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e;

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgSAF::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SAF) + ",";

    //////////////////////////////////////////////////////////////////////////////
    msg_body += NmeaParser::NumberToString(outputFrom);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
