#include "default_channels_config.h"

// Output is enabled
#define OUT_ENAB        true
#define OUT_DISAB       false

// User can enable/disable senidng of this message type
#define USER_ALLOW      true
#define USER_NOT        false


const int numberOfchannels = 3;
const int numberOfMsgs = 13;

bool allowedArray[numberOfMsgs][numberOfchannels] = {
    // Nmea_1    Nmea_2      UDP
    {OUT_ENAB, OUT_DISAB, OUT_ENAB},    // VBW   (is enabled on: NMEA_1, NMEA_2, UDP)
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},     // VLW
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},     // MTW
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},     // VHW
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},     // DPT
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},     // DPC
    {OUT_DISAB, OUT_DISAB, OUT_DISAB},      // ROT
    {OUT_DISAB, OUT_DISAB, OUT_DISAB},     // HDT
    {OUT_DISAB, OUT_DISAB, OUT_ENAB},    // DLR: skipper msg with DL2 measurements. Sent to display
    {OUT_DISAB, OUT_DISAB, OUT_ENAB},    // DLI: skipper msg with DL2 measurements/info. Sent to display
    {OUT_DISAB, OUT_DISAB, OUT_ENAB},    // DLM: skipper msg with DL2 measurements/info. Sent to display
    {OUT_ENAB, OUT_ENAB, OUT_ENAB},    // DATR: Raw data for external logging (DAT2, DAT3 and DATR sent)
    {OUT_DISAB, OUT_DISAB, OUT_DISAB}    // CUR: Water current layer - Multi-layer water current data ( IEC 61162-1_aed_2010.pdf, page 41.)
};

bool enabledArray[numberOfMsgs][numberOfchannels]= {
    // Nmea_1      Nmea_2      UDP
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // VBW   (if "USER_ALLOW", user can change enabled/disabled for this message on choosed output)
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // VLW
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // MTW
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // VHW
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // DPT
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},     // DPC
    {USER_NOT, USER_NOT, USER_NOT},     // ROT
    {USER_NOT, USER_NOT, USER_NOT},     // HDT
    {USER_NOT, USER_NOT, USER_NOT},      // DLR
    {USER_NOT, USER_NOT, USER_NOT},      // DLI
    {USER_NOT, USER_NOT, USER_NOT},      // DLI
    {USER_ALLOW, USER_ALLOW, USER_ALLOW},      // DATR
    {USER_ALLOW, USER_ALLOW, USER_ALLOW}       // CUR
};

QList<QString> Default_Channels_config::channelList = QList<QString>() << "Nmea_1" << "Nmea_2" << "UDPM";
QList<QString> Default_Channels_config::typeList = QList<QString>()<< "VBW" << "VLW" << "MTW" << "VHW" << "DPT"
                                                                   << "DPC" << "ROT" << "HDT"<<"DLR"<<"DLI"<<"DLM"<<"DATR"<<"CUR";
QList<QString> Default_Channels_config::alarmMsgList = QList<QString>()<< "ON" << "OFF";

Default_Channels_config::Default_Channels_config()
{

}

QList<QString> Default_Channels_config::getDefaultTypes()
{
    return typeList;
}

QList<bool> Default_Channels_config::getDefaultAllowed(QString channelName)
{
    QList<bool> result;
    int chNr = channelList.indexOf(channelName);
    if(chNr == -1)
        return result;

    for(int i = 0; i < typeList.length(); i++)
        result.append(allowedArray[i][chNr]);

    return result;
}

QList<bool> Default_Channels_config::getDefaultEnabled(QString channelName)
{
    QList<bool> result;
    int chNr = channelList.indexOf(channelName);
    if(chNr == -1)
        return result;

    for(int i = 0; i < typeList.length(); i++)
        result.append(enabledArray[i][chNr]);

    return result;
}
