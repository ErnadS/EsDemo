#include "msg_cfg.h"
#include "nmea/nmea_parser.h"

MsgCFG::MsgCFG()
{
    this->m_message_type_hash   = MsgCFG::CFGhash;
    this->m_message_type        = TYPE_CFG;
}


MsgCFG::MsgCFG(int systemID, int mode, int wTrackPowLev, int wTrackPulseLen, int wTrackRangeOffset,
               QString formats, int bTrackPowLev, int bTrackPulseLen, int bTrackRangeOffset, int pingMode)
{
    this->m_message_type_hash   = MsgCFG::CFGhash;
    this->m_message_type        = TYPE_CFG;

    this->systemID                 = systemID;
    this->mode                     = mode;
    this->wTrackPowLev             = wTrackPowLev;
    this->wTrackPulseLen           = wTrackPulseLen;
    this->wTrackRangeOffset        = wTrackRangeOffset;
    this->formats                  = formats;
    this->bTrackPowLev             = bTrackPowLev;
    this->bTrackPulseLen           = bTrackPulseLen;
    this->bTrackRangeOffset        = bTrackRangeOffset;
    this->pingMode                 = pingMode;
}

bool MsgCFG::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 10){
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
        mode                       = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        wTrackPowLev               = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        wTrackPulseLen             = NmeaParser::StringToInt(m_message_parameters[3], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        wTrackRangeOffset          = NmeaParser::StringToInt(m_message_parameters[4], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        formats                    = m_message_parameters[5];
        bTrackPowLev               = NmeaParser::StringToInt(m_message_parameters[6], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        bTrackPulseLen             = NmeaParser::StringToInt(m_message_parameters[7], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        bTrackRangeOffset          = NmeaParser::StringToInt(m_message_parameters[8], &ok);
        if(!ok) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }
        pingMode                   = NmeaParser::StringToInt(m_message_parameters[9], &ok);
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

QString MsgCFG::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_CFG) + "," + NmeaParser::NumberToString(systemID)
            + "," + NmeaParser::NumberToString(mode) + ","  + NmeaParser::NumberToString(wTrackPowLev) + "," +
            NmeaParser::NumberToString(wTrackPulseLen) + "," + NmeaParser::UintToString_FixedLength(wTrackRangeOffset, 2) + "," +
            formats;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
