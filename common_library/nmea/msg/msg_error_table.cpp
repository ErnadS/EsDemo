#include "msg_error_table.h"
#include "nmea/nmea_parser.h"

MsgERRORTABLE::MsgERRORTABLE()
{
    this->m_message_type_hash   = MsgERRORTABLE::ERRORTABLEhash;
    this->m_message_type        = TYPE_ERRORTABLE;
}


MsgERRORTABLE::MsgERRORTABLE(QList<unsigned> errorIDs, QList<unsigned> errorCounts)
{
    this->m_message_type_hash   = MsgERRORTABLE::ERRORTABLEhash;
    this->m_message_type        = TYPE_ERRORTABLE;

    this->errorIDs = errorIDs;
    this->errorCounts = errorCounts;

    this->m_message_type_hash   = MsgERRORTABLE::ERRORTABLEhash;
    this->m_message_type        = TYPE_ERRORTABLE;
}

bool MsgERRORTABLE::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 30){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        for (int i=0; i< m_message_parameters.size()/2; i++)
        {
            errorIDs.append( NmeaParser::StringToInt(m_message_parameters[i], &ok));
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
        }
        for (int i=m_message_parameters.size()/2; i< m_message_parameters.size(); i++)
        {
            errorCounts.append( NmeaParser::StringToInt(m_message_parameters[i], &ok));
            if(!ok) {
                m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
                return false;
            }
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

QString MsgERRORTABLE::getMsgBuffer()
{
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_ERRORTABLE) ;
    for (int i=0; i< errorIDs.length(); i++)
    {
        msg_body += ","+ NmeaParser::NumberToString(errorIDs[i]);
    }

    for (int i=0; i< errorIDs.length(); i++)
    {
        msg_body += ","+ NmeaParser::NumberToString(errorCounts[i]);
    }

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
