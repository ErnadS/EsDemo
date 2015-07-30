#include "msg_secu.h"
#include "nmea/nmea_parser.h"

MsgSECU::MsgSECU()
{
    this->m_message_type_hash   = MsgSECU::SECUhash;
    this->m_message_type        = TYPE_SECU;
}

MsgSECU::MsgSECU(QString serial, int option, int code)
{
    this->m_message_type_hash   = MsgSECU::SECUhash;
    this->m_message_type        = TYPE_SECU;

    this->serial = serial;
    this->option = option;
    this->code = code;
}

bool MsgSECU::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 3)
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    if ((m_message_parameters[0].length() > 6) || (m_message_parameters[1].length() > 6) || (m_message_parameters[2].length() > 6))
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    serial = m_message_parameters[0];

    if (serial.length() == 0)
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        option = NmeaParser::StringToInt(m_message_parameters[1], &ok);

        if (!ok)
        {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        code = NmeaParser::StringToInt(m_message_parameters[2], &ok);

        if (!ok)
        {
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

QString MsgSECU::getMsgBuffer()
{
    if (!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_SECU)
                      + "," + serial + "," + QString::number(option) + "," + QString::number(code);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
