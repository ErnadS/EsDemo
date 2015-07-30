#include "msg_cur.h"
#include "nmea/nmea_parser.h"

MsgCUR::MsgCUR()
{
    // TODO: FIX NMEA attribute
    //this->m_talker_id           = SystemConfiguration::getSourceTalker();
    this->m_message_type_hash   = MsgCUR::CURhash;
    this->m_message_type        = TYPE_CUR;
}

MsgCUR::MsgCUR(QString validityOfData, int dataSetNumber, int layerNumber, float currentDepthInMeters,
               float CurrentDirectionIndegrees, QString directionReferenceInUse, float currentSpeedInKnots,
               float referenceLayerDepthInMeters, float heading, QString headingReference,
               QString speedReference)
{

    // TODO: FIX NMEA attribute
    // this->m_talker_id                  = SystemConfiguration::getSourceTalker();
    this->m_message_type_hash          = MsgCUR::CURhash;
    this->m_message_type               = TYPE_CUR;
    // TODO: FIX NMEA attribute
    // this->m_number_of_decimals         = NmeaParser::getNumberOfDecimals();


    this->validityOfData               = validityOfData;
    this->dataSetNumber                = dataSetNumber;
    this->layerNumber                  = layerNumber;
    this->currentDepthInMeters         = currentDepthInMeters;
    this->CurrentDirectionIndegrees    = CurrentDirectionIndegrees;
    this->directionReferenceInUse      = directionReferenceInUse;
    this->currentSpeedInKnots          = currentSpeedInKnots;
    this->referenceLayerDepthInMeters  = referenceLayerDepthInMeters;
    this->heading                      = heading;
    this->headingReference             = headingReference;
    this->speedReference               = speedReference;


}

bool MsgCUR::setParams(QStringList m_message_parameters)
{
    if (m_message_parameters.count() != 11){
        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }

    try
    {
        bool ok;

        validityOfData                        = m_message_parameters[0];

        dataSetNumber                         = NmeaParser::StringToInt(m_message_parameters[1], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        layerNumber                           = NmeaParser::StringToInt(m_message_parameters[2], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        currentDepthInMeters                  = NmeaParser::StringToFloat(m_message_parameters[3], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        CurrentDirectionIndegrees             = NmeaParser::StringToFloat(m_message_parameters[4], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        directionReferenceInUse               = m_message_parameters[5];

        currentSpeedInKnots                   = NmeaParser::StringToFloat(m_message_parameters[6], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        referenceLayerDepthInMeters           = NmeaParser::StringToFloat(m_message_parameters[7], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        heading                               = NmeaParser::StringToFloat(m_message_parameters[8], &ok);
        if(!ok ) {
            m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
            return false;
        }

        headingReference                      = m_message_parameters[9];
        speedReference                        = m_message_parameters[10];

        return true;
    }
    catch (int e)
    {
        qDebug() << "Error 832. Exception: " << e;

        m_error_id = NmeaMessageErrorType::ERR_NMEA_FORMAT;
        return false;
    }
}

QString MsgCUR::getMsgBuffer()
{
    if(!m_message.isNull()&&!m_message.isEmpty())
        return m_message;
    QString msg_body= QString(m_talker_id) + QString(TYPE_CUR) + "," + validityOfData + "," +
            NmeaParser::NumberToString(dataSetNumber) + "," + NmeaParser::NumberToString(layerNumber) + "," +
            NmeaParser::NumberToString(currentDepthInMeters, 'f', 1) + "," +
            NmeaParser::NumberToString(CurrentDirectionIndegrees, 'f', 1) + "," +
            directionReferenceInUse + "," +
            NmeaParser::NumberToString(currentSpeedInKnots, 'f', m_number_of_decimals) + "," +
            NmeaParser::NumberToString(referenceLayerDepthInMeters, 'f', 1) + "," +
            NmeaParser::NumberToString(heading, 'f', 1) + "," + headingReference + "," +
            speedReference;

    m_message = this->addCrcToMsgBuffer(msg_body);
    return m_message;
}
