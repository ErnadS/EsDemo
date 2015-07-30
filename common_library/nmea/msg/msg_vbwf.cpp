#include "msg_vbwf.h"
#include "nmea/nmea_parser.h"

const QString MsgVBWF::msgSuffix = ",,,V,,V,,V";

MsgVBWF::MsgVBWF()
{
    this->m_message_type_hash   = MsgVBWF::VBWFhash;
    this->m_message_type        = TYPE_VBWF;
}

MsgVBWF::MsgVBWF(float forwardAvrSpeed, QString dataStatus)
{
    this->m_message_type_hash   = MsgVBWF::VBWFhash;
    this->m_message_type        = TYPE_VBWF;
    // TODO: FIX NMEA attribute
    // this->m_number_of_decimals  = NmeaParser::getNumberOfDecimals();

    this->forwardAvrSpeed          = forwardAvrSpeed;
    this->dataStatus               = dataStatus;
}

bool MsgVBWF::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 10){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        forwardAvrSpeed              = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        dataStatus                   = m_message_parameters[2];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;

    }
}

QString MsgVBWF::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body = QString(TALKER_SKIPPER) + QString(TYPE_VBWF)
            + "," + NmeaParser::NumberToString(forwardAvrSpeed, 'f', m_number_of_decimals) + ",," + dataStatus + msgSuffix;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
