#include "nmea_bauds_setup.h"

void NMEA_Bauds_Setup::getDefaults()
{
    {
        nmea_1_Baud = NMEA_Baud_S("Nmea_1", 4800);
        nmea_2_Baud = NMEA_Baud_S("Nmea_2", 4800);
        writeSetup();
    }
}

void NMEA_Bauds_Setup::readSetup()
{
    baudList = QList<NMEA_Baud_S>();
    if(SerializationController::Deserialize(baudList, "channels_bauds_setup", "/setup_files/")
            && !baudList.isEmpty())
    {
        nmea_1_Baud = baudList[0];
        nmea_2_Baud = baudList[1];
    }
    else
        getDefaults();
}

void NMEA_Bauds_Setup::writeSetup()
{
    baudList = QList<NMEA_Baud_S>();
    baudList.append(nmea_1_Baud);
    baudList.append(nmea_2_Baud);
    SerializationController::Serialize(baudList, "channels_bauds_setup", "/setup_files/");
}

NMEA_Bauds_Setup::NMEA_Bauds_Setup()
{
    readSetup();
}

int NMEA_Bauds_Setup::getChannelBaudRate(QString channelName) const
{
    if(channelName == nmea_1_Baud.getChannelName())
        return nmea_1_Baud.getChannelBaud();

    else //if(channelName == nmea_2_Baud.getChannelName())
        return nmea_2_Baud.getChannelBaud();
}

void NMEA_Bauds_Setup::setChannelBaudRate(QString channelName, int value)
{
    if((channelName == nmea_1_Baud.getChannelName()) && (nmea_1_Baud.getChannelBaud() != value))
        nmea_1_Baud.setChannelBaud(value);

    else if((channelName == nmea_2_Baud.getChannelName()) && (nmea_2_Baud.getChannelBaud() != value))
        nmea_2_Baud.setChannelBaud(value);

    writeSetup();
}

bool NMEA_Bauds_Setup::loadFromFile(QString fileSuffix)
{
    baudList = QList<NMEA_Baud_S>();
    if(SerializationController::Deserialize(baudList, "channels_bauds_setup" + fileSuffix, "/setup_files/saved_configs/")
            && !baudList.isEmpty())
    {
        nmea_1_Baud = baudList[0];
        nmea_2_Baud = baudList[1];
        return true;
    }
    else
    {
        return false;
    }
}

bool NMEA_Bauds_Setup::saveToFile(QString fileSuffix)
{
    baudList = QList<NMEA_Baud_S>();
    baudList.append(nmea_1_Baud);
    baudList.append(nmea_2_Baud);
    return SerializationController::Serialize(baudList, "channels_bauds_setup" + fileSuffix, "/setup_files/saved_configs/");
}
