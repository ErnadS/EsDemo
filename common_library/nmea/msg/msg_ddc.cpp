#include "msg_ddc.h"
#include "nmea/nmea_parser.h"

MsgDDC::MsgDDC()
{
    this->m_message_type_hash   = MsgDDC::DDChash;
    this->m_message_type        = TYPE_DDC;
}


MsgDDC::MsgDDC(QString dispDimmPreset, quint8 brightnes, QString coulorPalette, QString statusFlag)
{
    this->m_message_type_hash   = MsgDDC::DDChash;
    this->m_message_type        = TYPE_DDC;

    this->m_talker_id      = "VM";
    this->dispDimmPreset        = dispDimmPreset;
    this->brightnes             = brightnes;
    this->coulorPalette         = coulorPalette;
    this->statusFlag            = statusFlag;
}

bool MsgDDC::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() < 2)  // TODO: should be 4 params but skipper sends 2. Accept both 2 and 4 parameters
    {
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;

        dispDimmPreset          = m_message_parameters[0];
        brightnes               = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if (m_message_parameters.count() == 4) {
            coulorPalette           = m_message_parameters[2];
            statusFlag              = m_message_parameters[3];
        } else {
            coulorPalette = "";
            statusFlag = "C"; // "C" = command. TODO: wrong. if "C" is not received, it's not a command (IEC 61162)
        }

        if(brightnes < 0 || brightnes > 99){
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 845. Exception: " << e; // Different Error number?
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgDDC::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_DDC) + "," + dispDimmPreset + "," + NmeaParser::NumberToString(brightnes)+ "," + coulorPalette + "," + statusFlag;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
