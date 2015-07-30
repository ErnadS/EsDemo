#ifndef NMEA_DECIMALS_SETUP_H
#define NMEA_DECIMALS_SETUP_H

#include "nmea_use_two_decimals_s.h"

class NMEA_Decimals_Setup
{
    NMEA_Use_Two_Decimals_S nmea_1_Decimals;
    NMEA_Use_Two_Decimals_S nmea_2_Decimals;

    QList<NMEA_Use_Two_Decimals_S> decimalsList;

    void readSetup();
    void writeSetup();
public:
    NMEA_Decimals_Setup();

    bool getChannelDecimals(QString channelName) const;
    void setChannelDecimals(QString channelName, bool value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // NMEA_DECIMALS_SETUP_H

