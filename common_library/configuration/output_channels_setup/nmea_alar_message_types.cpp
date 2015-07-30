#include "nmea_alar_message_types.h"
#include <QDebug>

void NMEA_Alar_Message_Types::getDefaults()
{
    {
        alrMsgTypes.append(NMEA_Alarm_Message_Type_S("Nmea_1", "ON"));
        alrMsgTypes.append(NMEA_Alarm_Message_Type_S("Nmea_2", "ON"));
        alrMsgTypes.append(NMEA_Alarm_Message_Type_S("UDPM", "ON"));

        writeSetup();
    }
}

void NMEA_Alar_Message_Types::readSetup()
{
    alrMsgTypes = QList<NMEA_Alarm_Message_Type_S>();
    if(!SerializationController::Deserialize(alrMsgTypes, "alarm_msg_types_setup", "/setup_files/")
            || alrMsgTypes.isEmpty())
        getDefaults();
}

void NMEA_Alar_Message_Types::writeSetup()
{
    SerializationController::Serialize(alrMsgTypes, "alarm_msg_types_setup", "/setup_files/");
}

NMEA_Alar_Message_Types::NMEA_Alar_Message_Types()
{
    readSetup();
}

QString NMEA_Alar_Message_Types::getChannelAlarmMsgType(QString channelName) const
{
    for(int i = 0; i < alrMsgTypes.length(); i++)
        {
            if(alrMsgTypes[i].getChannelName() == channelName)
                return alrMsgTypes[i].getChannelAlarmMessageType();
        }

    return "OFF";
}

void NMEA_Alar_Message_Types::setChannelAlarmMsgType(QString channelName, QString value)
{
    for(int i = 0; i < alrMsgTypes.length(); i++)
        {
            if(alrMsgTypes[i].getChannelName() == channelName)
                alrMsgTypes[i].setChannelAlarmMessageType(value);
        }
    writeSetup();
}

bool NMEA_Alar_Message_Types::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(alrMsgTypes, "alarm_msg_types_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool NMEA_Alar_Message_Types::saveToFile(QString fileSuffix)
{
    //saved_configs/
    return SerializationController::Serialize(alrMsgTypes, "alarm_msg_types_setup" + fileSuffix, "/setup_files/saved_configs/");
}
