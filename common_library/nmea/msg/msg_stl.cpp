#include "msg_stl.h"
#include "nmea/nmea_parser.h"

MsgSTL::MsgSTL()
{
    this->m_message_type_hash   = MsgSTL::STLhash;
    this->m_message_type        = TYPE_STL;
}

MsgSTL::MsgSTL(float tripValue, float totalValue)
{
    this->m_message_type_hash   = MsgSTL::STLhash;
    this->m_message_type        = TYPE_STL;
    this->tripValue                = tripValue;
    this->totalValue               = totalValue;
}

bool MsgSTL::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 2){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        tripValue                  = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        totalValue                 = NmeaParser::StringToFloat(m_message_parameters[1], &ok);
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

QString MsgSTL::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;

    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_STL) + "," +
                     NmeaParser::NumberToString(tripValue, 'f',1) + "," +
                     NmeaParser::NumberToString(totalValue, 'f',1);


    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
