#include "nmea_decimals_setup.h"

void NMEA_Decimals_Setup::readSetup()
{
    decimalsList = QList<NMEA_Use_Two_Decimals_S>();
    if(SerializationController::Deserialize(decimalsList, "channels_decimal_setup", "/setup_files/")
            && !decimalsList.isEmpty())
    {
        nmea_1_Decimals = decimalsList[0];
        nmea_2_Decimals = decimalsList[1];
    }
    else
        getDefaults();

}

void NMEA_Decimals_Setup::writeSetup()
{
    decimalsList = QList<NMEA_Use_Two_Decimals_S>();
    decimalsList.append(nmea_1_Decimals);
    decimalsList.append(nmea_2_Decimals);
    SerializationController::Serialize(decimalsList, "channels_decimal_setup", "/setup_files/");
}

NMEA_Decimals_Setup::NMEA_Decimals_Setup()
{
    readSetup();
}

bool NMEA_Decimals_Setup::getChannelDecimals(QString channelName) const
{
    if(channelName == nmea_1_Decimals.getChannelName())
        return nmea_1_Decimals.getUseTwoDecimals();

    else //if(channelName == nmea_2_Baud.getChannelName())
        return nmea_2_Decimals.getUseTwoDecimals();
}

void NMEA_Decimals_Setup::setChannelDecimals(QString channelName, bool value)
{
    if((channelName == nmea_1_Decimals.getChannelName()) && (nmea_1_Decimals.getUseTwoDecimals() != value))
        nmea_1_Decimals.setUseTwoDecimals(value);

    else if((channelName == nmea_2_Decimals.getChannelName()) && (nmea_2_Decimals.getUseTwoDecimals() != value))
        nmea_2_Decimals.setUseTwoDecimals(value);

    writeSetup();
}

bool NMEA_Decimals_Setup::loadFromFile(QString fileSuffix)
{
    decimalsList = QList<NMEA_Use_Two_Decimals_S>();
    if(SerializationController::Deserialize(decimalsList, "channels_decimal_setup" + fileSuffix, "/setup_files/saved_configs/")
            && !decimalsList.isEmpty())
    {
        nmea_1_Decimals = decimalsList[0];
        nmea_2_Decimals = decimalsList[1];
        return true;
    }
    else
    {
        return false;
    }
}

bool NMEA_Decimals_Setup::saveToFile(QString fileSuffix)
{
    decimalsList = QList<NMEA_Use_Two_Decimals_S>();
    decimalsList.append(nmea_1_Decimals);
    decimalsList.append(nmea_2_Decimals);
    return SerializationController::Serialize(decimalsList, "channels_decimal_setup" + fileSuffix, "/setup_files/saved_configs/");
}

void NMEA_Decimals_Setup::getDefaults()
{
    {
        nmea_1_Decimals = NMEA_Use_Two_Decimals_S("Nmea_1", false);
        nmea_2_Decimals = NMEA_Use_Two_Decimals_S("Nmea_2", false);
        writeSetup();
    }
}
