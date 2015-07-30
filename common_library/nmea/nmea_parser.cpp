#include "nmea_parser.h"
#include "system_log/error_log/error_counter.h"

NmeaParser::NmeaParser()
{
}

NmeaMessage* NmeaParser::parse(QString message)
{
    QString message_body = message;
    QString m_talker_id;
    QString m_message_type;
    QString m_manufacturer_id;

    QString m_checksum;
    QStringList m_message_parameters;
    unsigned long msgHash;
    bool m_propriatary;

    ///////////////////////////////////////////////////////////////
    // Remove start byte
    ///////////////////////////////////////////////////////////////
    if(message_body[0]!='$' && message_body[0]!='!')
    {
        //nmeaMessage.error_ID=START_CHARACTER_ERROR; // NMEA messages must start with $.
        //NmeaMessage::errorCounter->emitSigError(ERR_TYPE_NMEA_FORMAT);
        MsgErr *msg = new MsgErr(NmeaMessageErrorType::START_CHARACTER_ERROR);
        msg->m_message = message;
        return msg;
    }
    else
        message_body.remove(0,1);

    if (message_body.length() > (MAX_NMEA__MSG_LENGTH - 1)) { // "$" is removed. therfore "- 1"
        MsgErr *msg = new MsgErr(NmeaMessageErrorType::ERR_MAX_LENGTH);
        msg->m_message = message;
        return msg;
    }
    // TODO: msg from sensor "$\n" crash (DNV testing)
if (message_body.length() < 5) {
    MsgErr *msg = new MsgErr(NmeaMessageErrorType::START_CHARACTER_ERROR);
    msg->m_message = message;
    return msg;
}
    ///////////////////////////////////////////////////////////////
    // Remove <CR><LF>
    ///////////////////////////////////////////////////////////////
    if(message_body[message_body.count()-1]!= '\n'||message_body[message_body.count()-2]!= '\r')
    {
        //NmeaMessage::errorCounter->emitSigError(ERR_TYPE_NMEA_FORMAT);
        MsgErr *msg = new MsgErr(NmeaMessageErrorType::END_CHARACTER_ERROR);  // NMEA message must terminate with <CR><LF>.
        msg->m_message = message;
        return msg;
    }
    else // remove new line
        message_body.remove(message_body.count()-2,2);


    // if we have something after CRC (as e.g. date ...), remove it.
    int asterInd = message_body.indexOf("*");
    if (asterInd > 0 && message_body.length() > (asterInd + 3)) {
        message_body = message_body.left(asterInd + 3);
    }

    ///////////////////////////////////////////////////////////////
    // CRC
    ///////////////////////////////////////////////////////////////
    m_message_parameters =message_body.split(",");

    int checksum_status = CRC8::validateCrc(message_body);

    if(checksum_status != NO_CRC)
    {
        QStringList temp = m_message_parameters[m_message_parameters.count()-1].split("*");

        if (temp.size() != 2)
        {
            MsgErr *msg = new MsgErr(NmeaMessageErrorType::CHECKSUM_ERROR);
            msg->m_message = message;
            return msg;
        }

        m_message_parameters[m_message_parameters.count()-1]=temp[0]; // replace last element with new without CRC
        m_checksum = temp[1];
        message_body.remove(message_body.indexOf("*"), message_body.count() - message_body.indexOf("*"));

        if(checksum_status!=CRC_8_OK)
        {
            MsgErr *msg = new MsgErr(NmeaMessageErrorType::CHECKSUM_ERROR);
            msg->m_message = message;
            return msg;
        }
    }

    if(message_body[0]=='P')
    {
        m_propriatary = true;

        if(m_message_parameters[0].count()<4) //||nmeaMessage.m_message_parameters[0].count()> 12) //8)
        {
            // Manufactor ID must be 3 characters and message type must be between 1 and 5 characters.
            MsgErr *msg = new MsgErr(NmeaMessageErrorType::MANUFACTURER_ID_MESSAGE_TYPE_ERROR);
            msg->m_message = message;
            return msg;
        }
        m_manufacturer_id = m_message_parameters[0].left(4); // Take a first 4 chars
        m_manufacturer_id = m_manufacturer_id.right(3);      // Remove "P" (Keep last 3 chars)
        m_message_type    = m_message_parameters[0].mid(4);     // Take all other chars
    }
    else
    {
        m_propriatary = false;
        if( m_message_parameters[0].count() < 4)
        {
            // Talker ID must be 2 characters and message type must be between 1 and 5 characters.
            MsgErr *msg = new MsgErr(NmeaMessageErrorType::TALKER_ID_MESSAGE_TYPE_ERROR);
            msg->m_message = message;
            return msg;
        }
        m_talker_id=m_message_parameters[0].left(2);
        m_message_type=m_message_parameters[0].mid(2);
    }

    m_message_parameters.removeAt(0);
    msgHash = calculateMessageTypeHash(m_message_type);
    NmeaMessage* nmeaMessage = createMessage(m_message_type, msgHash, m_message_parameters);

    // Update base class information
    nmeaMessage->setMsgInfo(m_talker_id, m_manufacturer_id, m_checksum, message, m_propriatary);

    return nmeaMessage;
}

// TODO: remove messages we are not using
NmeaMessage* NmeaParser::createMessage(QString message_type, unsigned long msgHash, QStringList m_message_parameters) {
    NmeaMessage* msg;

    switch (msgHash) {
    case MsgACK::ACKhash:
        msg = new MsgACK();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgACN::ACNhash:
        msg = new MsgACN();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgALC::ALChash:
        msg = new MsgALC();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgALF::ALFhash:
        msg = new MsgALF();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgAlmaSpeed::ALMASPEEDhash:
        msg = new MsgAlmaSpeed();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgAlmaTemp::ALMASTEMPhash:
        msg = new MsgAlmaTemp();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgALR::ALRhash:
        msg = new MsgALR();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgALRS::ALRShash:
        msg = new MsgALRS();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgARC::ARChash:
        msg = new MsgARC();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgBLNK::BLNKhash:
        msg = new MsgBLNK();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgCFG::CFGhash:
        msg = new MsgCFG();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgCPPC::CPPChash:
        msg = new MsgCPPC();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDAT::DAThash:
        msg = new MsgDAT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDDC::DDChash:
        msg = new MsgDDC();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDLI::DLIhash:
        msg = new MsgDLI();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDLM::DLMhash:
        msg = new MsgDLM();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDLR::DLRhash:
        msg = new MsgDLR();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDPT::DPThash:
        msg = new MsgDPT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgERRORCODE::ERRORCODEhash:
        msg = new MsgERRORCODE();
        msg->setParams(m_message_parameters);
        return msg;
    /*case MsgERRORTABLE::ERRORTABLEhash:  // Not input message
        msg = new MsgERRORTABLE();
        msg->setParams(m_message_parameters);
        return msg;
*/
    case MsgGCF::GCFhash:
        msg = new MsgGCF();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgGGA::GGAhash:
        msg = new MsgGGA();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgGLL::GLLhash:
        msg = new MsgGLL();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgHBT::HBThash:
        msg = new MsgHBT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgHDT::HDThash:
        msg = new MsgHDT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgMTW::MTWhash:
        msg = new MsgMTW();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgMTWF::MTWFhash:
        msg = new MsgMTWF();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgPNG::PNGhash:
        msg = new MsgPNG();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgRCF::RCFhash:
        msg = new MsgRCF();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgRMC::RMChash:
        msg = new MsgRMC();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgROT::ROThash:
        msg = new MsgROT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgRSTT::RSTThash:
        msg = new MsgRSTT();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgSFS::SFShash:
        msg = new MsgSFS();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgSCF::SCFhash:
        msg = new MsgSCF();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgSNF::SNFhash:
        msg = new MsgSNF();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgTHS::THShash:
        msg = new MsgTHS();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgTST::TSThash:
        msg = new MsgTST();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVBW::VBWhash:
        msg = new MsgVBW();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVBWF::VBWFhash:
        msg = new MsgVBWF();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVHW::VHWhash:
        msg = new MsgVHW();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVLW::VLWhash:
        msg = new MsgVLW();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVMPCGTER::VMPCGTERhash:
        msg = new MsgVMPCGTER();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgVTG::VTGhash:
        msg = new MsgVTG();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgZDA::ZDAhash:
        msg = new MsgZDA();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgZTG::ZTGhash:
        msg = new MsgZTG();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgDATR::DATRhash:
        msg = new MsgDATR();
        msg->setParams(m_message_parameters);
        return msg;
    case MsgSTL::STLhash:
        msg = new MsgSTL();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgCUR::CURhash:
        msg = new MsgCUR();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgICM::ICMhash:
        msg = new MsgICM();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgIDM::IDMhash:
        msg = new MsgIDM();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgVER::VERhash:
        msg = new MsgVER();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgDTL::DTLhash:
        msg = new MsgDTL();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgSAF::SAFhash:
        msg = new MsgSAF();
        msg->setParams(m_message_parameters);
        return msg;

    case MsgSECU::SECUhash:
        msg = new MsgSECU();
        msg->setParams(m_message_parameters);
        return msg;

    default:
        return new MsgUnknown(message_type);
    }
}

unsigned long NmeaParser::calculateMessageTypeHash(QString message_type)
{
    unsigned long hash = 0;

    if (message_type == "01")
        return 1;

    if (message_type == "06")
        return 6;

    // Problem migt occur if message type is loger than 3 characters (possible for propriatary msgs?)
    // Use only last 3 characters of msg type for calculating MessageTypeHash - is it possible to have
    // multiple propriatary msgs with same 3 last characters in msg type?
    /*
    int i;
    if (message_type.count() < 3) {
        for(i=0; i<message_type.count(); i++) {
            hash = hash * 256;
            hash += message_type[i].toAscii();
        }
    } else {
        for(i=message_type.count()-3;i<message_type.count();i++)
        {
            hash = hash * 256;
            hash += message_type[i].toAscii();
        }
    }
    */

    return hash;
}

float NmeaParser::StringToFloat(QString string, bool *ok)
{
    if(ok != 0)
        *ok = true;
    if(string.isEmpty())
        return std::numeric_limits<float>::max();
    else
        return string.toFloat(ok);
}

float NmeaParser::StringToInt(QString string, bool *ok)
{
    if(ok != 0)
        *ok = true;
    if(string.isEmpty())
        return std::numeric_limits<int>::max();
    else
        return string.toInt(ok);
}

QString NmeaParser::NumberToString(const int number)
{
    if(number == std::numeric_limits<int>::max())
        return "";
    else
        return QString::number(number);
}

QString NmeaParser::NumberToString(const float number, const char format, int precision)
{
    if(number == std::numeric_limits<float>::max())
        return "";
    else
        return QString::number(number,  format, precision);
}

QString NmeaParser::NumberToDisplayString(const int number)
{
    QString result = NumberToString(number);

    if(result == "")
        result = "-.-";

    return result;
}

QString NmeaParser::NumberToDisplayString(const float number, const char format, int precision)
{
    QString result = NumberToString(number, format, precision);

    if(result == "")
        result = "-.-";

    return result;
}

QString NmeaParser::NumberToStringSigned(const int number)
{
    if(number == std::numeric_limits<int>::max())
        return "";
    if(number>0)
        return ("+" + QString::number(number));
    else
        return QString::number(number);

}

QString NmeaParser::NumberToStringSigned(const float number, const char format, int const precision)
{
    if(number == std::numeric_limits<float>::max())
        return "";
    if(number>0)
        return ("+" + QString::number(number,  format, precision));
    else
        return QString::number(number,  format, precision);
}

unsigned long NmeaParser::StringToULong(const QString string, bool *ok)
{
    if(ok != 0)
        *ok = true;
    if(string.isEmpty())
        return std::numeric_limits<unsigned long>::max();
    else
        return string.toULong(ok);
}

QString NmeaParser::UlongToString(const unsigned long number)
{
    if(number == std::numeric_limits<unsigned long>::max())
        return "";
    else
        return QString::number(number);
}

QString NmeaParser::UlongToString_FixedLenght(const unsigned long number, const int NoOfLeadingZero)
{
    if(number == std::numeric_limits<unsigned long>::max())
        return "";
    else
        return QString("%1").arg(number, NoOfLeadingZero, 'd', 0, '0');
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// e.g. convert "1" to "001" or "0001"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NmeaParser::UintToString_FixedLength(const quint32 number, const int NoOfLeadingZero) {
    return QString("%1").arg(number, NoOfLeadingZero, 'd', 0, '0');
    // "number": number that’s going to be converted
    // "NoOfLeadingZero": width of the field I want to fill
    // "d": (f’->float, ‘d’->integer, etc)
    // "0": precision after desimal point (if used)
    // "'0'":  padding character
}

QString NmeaParser::IntToString_FixedLength(const int number, const int NoOfLeadingZero)
{
    return QString("%1").arg(number, NoOfLeadingZero, 'd', 0, '0');
    // "number": number that’s going to be converted
    // "NoOfLeadingZero": width of the field I want to fill
    // "d": (f’->float, ‘d’->integer, etc)
    // "0": precision after desimal point (if used)
    // "'0'":  padding character
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// e.g. convert "1.467" to "001.5"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NmeaParser::FloatToString_FixedLength(const float number, const int NoOfLeadingZero, const int precision) {
    // Note: other parameter is total number of chars including separator and precision. Therfore we have:
    // NoOfLeadingZero + 1 + precision. Sow if you want 3 leading zeros and one decimal point, other parameter is 5 (e.g. 002.0 => 4 numbers + 1 desimal separator)
    return QString("%1").arg(number, NoOfLeadingZero + 1 + precision, 'f', precision, '0'); // 3 ciffer (e.g. 002)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// e.g. convert "1.467" to "+001.5"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NmeaParser::FloatToString_FixedLength_Signed(const float number, const int NoOfLeadingZero, const int precision) {
    // Note: other parameter is total number of chars including separator and precision. Therfore we have:
    // NoOfLeadingZero + 1 + precision. Sow if you want 3 leading zeros and one decimal point, other parameter is 5 (e.g. 002.0 => 4 numbers + 1 desimal separator)
    float unsignedNumber;

   bool positive = true;
   if (number < 0) {
       positive = false;
       unsignedNumber = number * (-1);  // remove sign
   }
   else
   {
       unsignedNumber = number;
   }

    QString result = QString("%1").arg(unsignedNumber, NoOfLeadingZero + 1 + precision, 'f', precision, '0');

    if (positive)
        return "+" + result;
    else
        return "-" + result;
}

bool NmeaParser::isNumberValidInt(const int value)
{
    return (value != std::numeric_limits<int>::max());
}

bool NmeaParser::isNumberValidFloat(const float value)
{
    return (value != std::numeric_limits<float>::max());
}


