#include "msg_datr.h"
#include "nmea/nmea_parser.h"

MsgDATR::MsgDATR()
{
    this->m_message_type_hash   = MsgDATR::DATRhash;
    this->m_message_type        = TYPE_DATR;
}

MsgDATR::MsgDATR(float latitude, QString northOrSouth, float longitude, QString eastOrWest,
                 QString utcOfData, float sog, float cog, float depth, float depthMode, quint32 nCurrentSeaCalibLeg, quint32 nCurrentSeaCalibDistance)
{
    this->m_message_type_hash   = MsgDATR::DATRhash;
    this->m_message_type        = TYPE_DATR;

    this->latitude              = latitude;
    this->northOrSouth          = northOrSouth;
    this->longitude             = longitude;
    this->eastOrWest            = eastOrWest;
    this->utcOfData             = utcOfData;
    this->sog                   = sog;
    this->cog                   = cog;
    this->depth                 = depth;

    this->depthMode             = depthMode;
    this->nCurrentSeaCalibLeg         = nCurrentSeaCalibLeg;
    this->nCurrentSeaCalibDistance         = nCurrentSeaCalibDistance;
}

bool MsgDATR::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;
        latitude                              = NmeaParser::StringToFloat(m_message_parameters[0], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        northOrSouth                          = m_message_parameters[1];

        longitude                             = NmeaParser::StringToFloat(m_message_parameters[2], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        eastOrWest                            = m_message_parameters[3];
        utcOfData                             = m_message_parameters[4];

        sog                                   = NmeaParser::StringToFloat(m_message_parameters[5], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        cog                                   = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        depth                                 = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        depthMode                                 = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }


        nCurrentSeaCalibLeg                                 = NmeaParser::StringToInt(m_message_parameters[9], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        nCurrentSeaCalibDistance                                 = NmeaParser::StringToInt(m_message_parameters[10], &ok);
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

QString MsgDATR::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(TALKER_SKIPPER) + QString(TYPE_DATR) + "," +
            NmeaParser::NumberToString(latitude, 'f',1) + "," +
            northOrSouth + "," +
            NmeaParser::NumberToString(longitude, 'f',1) + "," +
            eastOrWest + "," +
            utcOfData + "," +
            NmeaParser::NumberToString(sog, 'f',1) + "," +
            NmeaParser::NumberToString(cog, 'f',1) + "," +
            NmeaParser::NumberToString(depth, 'f',1) + "," +
            NmeaParser::NumberToString(depthMode, 'f',1)+ "," +
            QString::number(nCurrentSeaCalibLeg)+ "," +
            QString::number(nCurrentSeaCalibDistance);

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
