#ifndef NMEAMESSAGE_H
#define NMEAMESSAGE_H

#include "system_log/error_log/error_counter.h"  // all messages are logging if format wrong

//////////////////////////////////////////////////////////////
// NMEA 0183 (http://en.wikipedia.org/wiki/NMEA_0183)
// The National Marine Electronics Association (NMEA)
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// Standard message (http://aprs.gids.nl/nmea/#allgp):
// ***********************************************************
// $GPGGA,23,2,3*7A<CR><LF>  (example)
//
// GP is the talker ID (1 or 2 letter)
// GGA is the message type
//
// 23 is the first message parameter
// 2 is the second message parameter
// 3 is the third message parameter
// Number of message parameters vary between concrete message
// types but each are separated by a comma
//
// 7A is the checksum calculated as letterwise XOR of:
// GPGGA,23,2,3 ($ and * are not used for checksum calculation)
// <CR> is the carriage return character ('\r')
// <LF> is the line feed charater ('\n')


//////////////////////////////////////////////////////////////
// Proprietary Sentences:
// ***********************************************************
// $PELRGGA,34,23*4C<CR><LF>  (example)
// P stands for "Proprietary" (1 letter, if "P" => Proprietary)
// ELR stands 3 letter manufacturer ID (ELR - Elreg)
// The rest is the same like in the standard message
//////////////////////////////////////////////////////////////

#define TALKER_SKIPPER                 "PSKP"

/////////////////////////////////////////////////////////////
// Implemented - (I), not implemented - (NI)
/////////////////////////////////////////////////////////////
// DL1
/////////////////////////////////////////////////////////////
#define TYPE_ALMA_SPEED                "01"     // (I) Proprietary - Multiple systems/System specific?
#define TYPE_ALMA_TEMP                 "06"     // (I) Proprietary - Multiple systems/System specific?
#define TYPE_CFG                       "CFG"    // (I) Proprietary - Multiple systems?
#define TYPE_DAT                       "DAT"    // (I) Proprietary - Multiple systems?
#define TYPE_DATR                      "DATR"   // (I) Proprietary - Multiple systems?
#define TYPE_DIAG                      "DIAG"   // (NI) Proprietary - Multiple systems?
#define TYPE_FMUP                      "FMUP"   // (NI) Proprietary - System specific (DL1 firmware update message)
#define TYPE_MTWF                      "MTWF"   // (I) Proprietary - Multiple systems/System specific?
#define TYPE_RAW                       "RAW"    // (NI) Proprietary - Multiple systems/System specific?
#define TYPE_SNF                       "SNF"    // (I) Proprietary - Multiple systems/System specific?
#define TYPE_TST                       "TST"    // (I) Proprietary - Multiple systems?
#define TYPE_VBWF                      "VBWF"   // (I) Proprietary - Multiple systems/System specific?

/////////////////////////////////////////////////////////////
// DL2
/////////////////////////////////////////////////////////////
#define TYPE_BLNK                       "BLNK"    // (I) Proprietary - System specific
#define TYPE_PNG                        "PNG"     // (I) Proprietary - System specific


/////////////////////////////////////////////////////////////
// DL21
/////////////////////////////////////////////////////////////
// OUTPUT:
#define TYPE_SOGL                      "SOGL"   // (NI) Proprietary - Multiple systems/System specific?
#define TYPE_SOGT                      "SOGT"   // (NI) Proprietary - Multiple systems/System specific?
#define TYPE_STWL                      "STWL"   // (NI) Proprietary - Multiple systems/System specific?
#define TYPE_STWT                      "STWT"   // (NI) Proprietary - Multiple systems/System specific?
#define TYPE_TEMP                      "TEMP"   // (NI) Proprietary - Multiple systems/System specific?

// INPUT:
#define TYPE_ACF                       "ACF"    // (NI) Proprietary - Multiple systems/System specific?


/////////////////////////////////////////////////////////////
// Skipper Proprietary (used for errors)
/////////////////////////////////////////////////////////////
#define TYPE_ERRORTABLE                "ERRORTABLE"    // (I)
#define TYPE_ERRORCODE                 "ERRORCODE"     // (I)
#define TYPE_VMPCGTER                  "VMPCGTER"      // (I)
#define TYPE_CPPC                      "CPPC"          // (I)
#define TYPE_SECU                      "SECU"           // (I)

/////////////////////////////////////////////////////////////
// Messages for communication between JB70 and CU-M001
/////////////////////////////////////////////////////////////
#define TYPE_DLR                        "DLR"    // (I) All measured values for display.
#define TYPE_DLI                        "DLI"    // (I) All info values for display.
#define TYPE_DLM                        "DLM"    // (I)

#define TYPE_SFS                        "SFS"    // (I) Message for speed simulation.
#define TYPE_ALRS                       "ALRS"   // (I) Alarm message for display unit.


/////////////////////////////////////////////////////////////
#define TYPE_ICM                        "ICM"    // (I) Internal communication message (should replace all msgs bellow).
#define TYPE_IDM                        "IDM"    // (I) Internal diagnostics message
/////////////////////////////////////////////////////////////

//#define TYPE_SCM                        "SCM"    // (I) Speed calibration manual.
//#define TYPE_DFC                        "DFC"    // (I) Data for calibration, from JB to Display.

//#define TYPE_SMCF                       "SMCF"   // (I) "Send Me Configuration"
//#define TYPE_CAC                        "CAC"    // (I) Calibration command

//#define TYPE_FCM                        "FCM"    // (I) Fitness confirm message and alarm ack, from display.
#define TYPE_TIME                       "TIME"   // (I) Time information
#define TYPE_RSTT                       "RSTT"   // (I) Trip reset, for reseting "distance since reset".
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Service Software search commands
/////////////////////////////////////////////////////////////
#define TYPE_GCF                        "GCF"    // (I)
#define TYPE_RCF                        "RCF"    // (I)
#define TYPE_SCF                        "SCF"    // (I)

#define TYPE_STL                        "STL"    // (I)


/////////////////////////////////////////////////////////////
// Service Software commands
/////////////////////////////////////////////////////////////
#define TYPE_RSTO                       "RSTO"   // (I)

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Data logging
/////////////////////////////////////////////////////////////
#define TYPE_DTL                       "DTL"   // (I)
#define TYPE_SAF                       "SAF"   // (I)

/////////////////////////////////////////////////////////////


// STANDARD NMEA MESSAGES
/////////////////////////////////////////////////////////////
#define TYPE_ACN                       "ACN"    // (I)
#define TYPE_ACK                       "ACK"    // (I)
#define TYPE_ALR                       "ALR"    // (I)
#define TYPE_GGA                       "GGA"    // (I)
#define TYPE_HDT                       "HDT"    // (I)
#define TYPE_MTW                       "MTW"    // (I)
#define TYPE_VBW                       "VBW"    // (I)
#define TYPE_VHW                       "VHW"    // (I)
#define TYPE_VLW                       "VLW"    // (I)
#define TYPE_VTG                       "VTG"    // (I)
#define TYPE_ROT                       "ROT"    // (I)
#define TYPE_HBT                       "HBT"    // (I)
#define TYPE_ALC                       "ALC"    // (I)
#define TYPE_ARC                       "ARC"    // (I)
#define TYPE_RMC                       "RMC"    // (I)
#define TYPE_ZDA                       "ZDA"    // (I)
#define TYPE_ZTG                       "ZTG"    // (I)
#define TYPE_ALF                       "ALF"    // (I)
#define TYPE_DDC                       "DDC"    // (I)
#define TYPE_THS                       "THS"    // (I)
#define TYPE_GLL                       "GLL"    // (I)
#define TYPE_DPT                       "DPT"    // (I)
#define TYPE_CUR                       "CUR"    // (I)
#define TYPE_VER                       "VER"    // (I)


/////////////////////////////////////////////////////////////
#define TYPE_ERR                        "ERR"

#define TYPE_UNKNOWN                    "UNKNOWN"
/////////////////////////////////////////////////////////////
// TODO: remove later, just for test
/////////////////////////////////////////////////////////////
#define TYPE_ALR_TST                        "ALT"
#define TYPE_NMEA_TST                       "REC"
#define TYPE_INFO                           "INFO"

// #include "nmeaparser.h"
#include "QStringList"
#include "utility/Crc8.h"
#include <limits>

//////////////////////////////////////////////////////////////////////////////////////////////////
// FROM THE NMEA STANDARD:
//////////////////////////////////////////////////////////////////////////////////////////////////
// NMEA 0183 sentences vary in length, but each sentence is limited to 79 characters or
// less. This length limit excludes the $ and the [CR][LF] characters. The data field block,
// including delimiters is limited to 74 characters or less.
// 79 + 3 = 82
//////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_NMEA__MSG_LENGTH  82

enum class NmeaMessageErrorType
{
    NO_NMEA_ERROR,                              // Message OK!
    START_CHARACTER_ERROR,                 // NMEA messages must start with $ or !.
    MANUFACTURER_ID_MESSAGE_TYPE_ERROR,    // Manufacturer ID must be 3 characters and message type must be between 1 and 5 characters.
    TALKER_ID_MESSAGE_TYPE_ERROR,          // Talker ID must be 2 characters and message type must be between 1 and 5 characters.
    MAX_PARAMETER_NUMBER_ERROR,            // Maximum NMEA parameter number exceeded.
    MAX_PARAMETER_LENGHT_ERROR,            // Maximum NMEA parameter length exceeded.
    CHECKSUM_LENGHT_ERROR,                 // CRC8 is used as check sum, therefore the check sum must have 2 hex chars.
    END_CHARACTER_ERROR,                   // NMEA message must terminate with <CR><LF>.
    CHECKSUM_ERROR,                        // NMEA message checksum is wrong.
    ERR_NMEA_FORMAT,
    ERR_MAX_LENGTH
};

class NmeaMessage
{
public:
    QString m_talker_id;
    QString m_manufacturer_id;
    bool m_proprietary;
    QString m_message_type;
    unsigned long m_message_type_hash;
    QString m_message;
    QString m_checksum;
    NmeaMessageErrorType m_error_id;

    int m_number_of_decimals;

    NmeaMessage();
    virtual ~NmeaMessage();

    // Implemented in NmeaMessage.cpp
    void setMsgInfo(QString m_talker_id, QString m_manufacturer_id, QString crc, QString m_messageString, bool m_proprietary);
    QString addCrcToMsgBuffer(QString body);

    // Pure virtual (implemented in child classes)
    virtual bool setParams(QStringList m_message_parameters) = 0;
    virtual QString getMsgBuffer() = 0;
    virtual NmeaMessage* clone() = 0;

    QString talkerId() const;
    QString manufacturerId() const;
    QString messageType() const;
    bool isPropriatary() const;

    QString checksum() const;
    unsigned long messageTypeHash() const;
    NmeaMessageErrorType errorType() const;

    int number_of_decimals() const;
    void setNumber_of_decimals(int number_of_decimals);
    bool propriatary() const;
    void setPropriatary(bool propriatary);
};

#endif // NMEAMESSAGE_H
