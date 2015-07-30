#include "singlechannelsetup.h"
#include <QDebug>


int SingleChannelSetup::getChannelBaudRate() const
{
    return channelBaudRate;
}

void SingleChannelSetup::setChannelBaudRate(int value)
{
    channelBaudRate = value;
}
void SingleChannelSetup::getDefaults()
{
    {
        channelMsgs.clear();

        QList<QString> defaultTypes = Default_Channels_config :: getDefaultTypes();
        QList<bool> defaultAllowed = Default_Channels_config :: getDefaultAllowed(channelname);
        QList<bool> defaultEnabled = Default_Channels_config :: getDefaultEnabled(channelname);

        for(int i = 0; i < defaultTypes.length(); i++)
            channelMsgs.append(Sing_Ch_Sing_Msg_S(defaultTypes[i], defaultAllowed[i], defaultEnabled[i]));

        writeSetup();
    }
}

void SingleChannelSetup::readSetup()
{
    if (!SerializationController::Deserialize(channelMsgs, channelname + "_channel_setup", "/setup_files/") ||
            channelMsgs.length() != Default_Channels_config :: getDefaultTypes().length())
    getDefaults();
}

void SingleChannelSetup::writeSetup()
{
    SerializationController::Serialize(channelMsgs, channelname + "_channel_setup", "/setup_files/");
}

SingleChannelSetup::SingleChannelSetup()
{
}

SingleChannelSetup::SingleChannelSetup(int channelBaudRate, QString channelname)
{
    this->channelBaudRate = channelBaudRate;
    this->channelname = channelname;
    readSetup();
}

QList<QString> SingleChannelSetup::getMsgsTypes()
{
    QList<QString> result;

    for(int i = 0; i < channelMsgs.length(); i++)
        result.append(channelMsgs[i].getMsgType());

    return result;
}

QList<bool> SingleChannelSetup::getMsgsAllowed()
{
    QList<bool> result;

    for(int i = 0; i < channelMsgs.length(); i++)
        result.append(channelMsgs[i].getAllowed());

    return result;
}

QList<bool> SingleChannelSetup::getMsgsEnabled()
{
    QList<bool> result;

    for(int i = 0; i < channelMsgs.length(); i++)
        result.append(channelMsgs[i].getEnabled());

    return result;
}

QList<QString> SingleChannelSetup::getAvailableMsgsTypes()
{
    QList<QString> result;

    for(int i = 0; i < channelMsgs.length(); i++)
        if(channelMsgs[i].getAllowed())
            result.append(channelMsgs[i].getMsgType());

    return result;
}

QList<bool> SingleChannelSetup::getAvailableMsgsEnabled()
{
    QList<bool> result;

    for(int i = 0; i < channelMsgs.length(); i++)
        if(channelMsgs[i].getAllowed())
            result.append(channelMsgs[i].getEnabled());

    return result;
}

void SingleChannelSetup::setMsgsEnabled(QList<QString> msgTypes, QList<bool> newEnabled)
{
    for (int i = 0; i < msgTypes.length(); i++)
    {
        for(int j = 0; j < channelMsgs.length(); j++)
            if (channelMsgs[j].getMsgType() == msgTypes[i])
            {
                channelMsgs[j].setEnabled(newEnabled[i]);
                break;
            }
    }
    writeSetup();
}

void SingleChannelSetup::setMsgsEnabled(QString msgType, bool newEnable)
{
    QList<QString> msgTypes;
    msgTypes.append(msgType);

    QList<bool> newEnabled;
    newEnabled.append(newEnable);
    setMsgsEnabled(msgTypes, newEnabled);
}

// TODO:change this to get from QJson
bool SingleChannelSetup::isAlarmOutputEnabled() {
    return true;
}

bool SingleChannelSetup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(channelMsgs, channelname + "_channel_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool SingleChannelSetup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(channelMsgs, channelname + "_channel_setup" + fileSuffix, "/setup_files/saved_configs/");
}
