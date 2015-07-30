#ifndef NMEA_BAUDS_SETUP_H
#define NMEA_BAUDS_SETUP_H

#include "nmea_baud_s.h"

class NMEA_Bauds_Setup
{
    NMEA_Baud_S nmea_1_Baud;
    NMEA_Baud_S nmea_2_Baud;

    QList<NMEA_Baud_S> baudList;

    void readSetup();
    void writeSetup();
public:
    NMEA_Bauds_Setup();

    int getChannelBaudRate(QString channelName) const;
    void setChannelBaudRate(QString channelName, int value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // NMEA_BAUDS_SETUP_H
