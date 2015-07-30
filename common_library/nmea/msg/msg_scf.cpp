#include "msg_scf.h"
#include "nmea/nmea_parser.h"

MsgSCF::MsgSCF()
{
    this->m_message_type_hash   = MsgSCF::SCFhash;
    this->m_message_type        = TYPE_SCF;
}

MsgSCF::MsgSCF(QString systemName, QString ip, QString sfi, QString destSfi, quint8 group)
{
    this->m_message_type_hash   = MsgSCF::SCFhash;
    this->m_message_type        = TYPE_SCF;

    this->systemName    = systemName;
    this->ip            = ip;

    this->sfi           = sfi;
    this->destSfi       = destSfi;

    this->group = group;
}


bool MsgSCF::setParams(QStringList m_message_parameters)
{
    bool ok;

    if (m_message_parameters.count() != 8){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        systemName  = m_message_parameters[0];
        ip  = m_message_parameters[1] + "." + m_message_parameters[2] + "." + m_message_parameters[3] + "." + m_message_parameters[4];
        sfi  = m_message_parameters[5];
        destSfi  = m_message_parameters[6];
        group  = NmeaParser::StringToInt(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e; // Different Error number?
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
    return false;
}

QString MsgSCF::getMsgBuffer()
{
    return ""; // not used. Received from Service Software
}

