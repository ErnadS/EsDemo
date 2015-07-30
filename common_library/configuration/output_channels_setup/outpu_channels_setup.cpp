#include "outpu_channels_setup.h"

int defaultBaud = 4800;
QList<int> Outpu_Channels_Setup::getAvailableMsgsEnabled(int index)
{
    QList<int> result;
    QList<bool> enabled = outputChannels[index].getAvailableMsgsEnabled();

    for(int i = 0; i < enabled.length(); i++)
        if(enabled[i])
            result.append(1);
    else
            result.append(0);

    return result;
}

Outpu_Channels_Setup::Outpu_Channels_Setup()
{
    chSetupReceivedFlag = QList<bool>();
    for(int i = 0; i < Default_Channels_config::channelList.length(); i++)
    {
        outputChannels.append(SingleChannelSetup(defaultBaud, Default_Channels_config::channelList[i]));
        chSetupReceivedFlag.append(false);
    }
}

MsgICM *Outpu_Channels_Setup::getChannelSetupMessage(QString chName)
{
    QList<int> msgParameters = QList<int>();

    int index = Default_Channels_config::channelList.indexOf(chName);
    msgParameters<<index << nmeaBauds.getChannelBaudRate(chName);

    msgParameters<<Default_Channels_config::alarmMsgList.indexOf(nmeaAlrTypes.getChannelAlarmMsgType(chName));

    msgParameters<<nmeaDecimals.getChannelDecimals(chName);

    QList<QString> msgNmeaTypeList = outputChannels[index].getAvailableMsgsTypes();
    QList<int> msgNmeaSendingState = getAvailableMsgsEnabled(index);

    for(int i = 0; i < msgNmeaTypeList.length(); i++)
        {
            msgParameters<<Default_Channels_config::typeList.indexOf(msgNmeaTypeList[i]);
            msgParameters<<msgNmeaSendingState[i];
        }

    return new MsgICM(OCFsetupCommand, msgParameters);
}

void Outpu_Channels_Setup::setChannel(QList<int> msgParameters)
{
    int chIndex = msgParameters[0];
    QString msgChannelName = Default_Channels_config::channelList[chIndex];
    int msgBaudRate = msgParameters[1];

    QString msgAlarmMsgType = Default_Channels_config::alarmMsgList[msgParameters[2]];
    bool useTwoDecimals = bool(msgParameters[3]);

    QList<QString> msgNmeaTypeList = QList<QString>();
    QList<bool> msgNmeaSendingState = QList<bool>();

    for(int i = 4; i < msgParameters.length(); i += 2)
        {
            msgNmeaTypeList<<Default_Channels_config::typeList[msgParameters[i]];
            msgNmeaSendingState<<msgParameters[i + 1];
        }

    outputChannels[chIndex].setMsgsEnabled(msgNmeaTypeList, msgNmeaSendingState);

    chSetupReceivedFlag[chIndex] = true;

    nmeaBauds.setChannelBaudRate(msgChannelName, msgBaudRate);
    nmeaAlrTypes.setChannelAlarmMsgType(msgChannelName, msgAlarmMsgType);
    nmeaDecimals.setChannelDecimals(msgChannelName, useTwoDecimals);
}

void Outpu_Channels_Setup::setEnabled(QString chName, QString msgType, bool enable)
{
    int index = Default_Channels_config::channelList.indexOf(chName);
    if (index == -1)
        return;
    outputChannels[index].setMsgsEnabled(msgType, enable);
}

bool Outpu_Channels_Setup::isEnabled(QString msgType, QString chName)
{
    int index = Default_Channels_config::channelList.indexOf(chName);
    if (index == -1)
        return false;

    int index1 = outputChannels[index].getMsgsTypes().indexOf(msgType);
    if (index1 == -1)
        return false;

    return outputChannels[index].getMsgsEnabled()[index1];
}

bool Outpu_Channels_Setup::isEnabledByAny(QString msgType)
{
    foreach (QString ch, Default_Channels_config::channelList)
        if(isEnabled(msgType, ch))
            return true;

    return false;
}

int Outpu_Channels_Setup::getChannelBaudRate(QString chName) const
{
    return nmeaBauds.getChannelBaudRate(chName);
}

void Outpu_Channels_Setup::setChannelBaudRate(QString chName, int value)
{
    nmeaBauds.setChannelBaudRate(chName, value);
}

bool Outpu_Channels_Setup::getChannelUseTwoDecimals(QString chName) const
{
    return nmeaDecimals.getChannelDecimals(chName);
}

void Outpu_Channels_Setup::setChannelUseTwoDecimals(QString chName, bool value)
{
    nmeaDecimals.setChannelDecimals(chName, value);
}

QString Outpu_Channels_Setup::getChannelAlarmMsgType(QString chName) const
{
    return nmeaAlrTypes.getChannelAlarmMsgType(chName);
}

void Outpu_Channels_Setup::setChannelAlarmMsgType(QString chName, QString value)
{
    nmeaAlrTypes.setChannelAlarmMsgType(chName, value);
}

QList<QString> Outpu_Channels_Setup::getAvailableMsgsTypes(QString chName)
{
    int index = Default_Channels_config::channelList.indexOf(chName);
    if (index == -1)
        return QList<QString>();

    return outputChannels[index].getAvailableMsgsTypes();
}

QList<bool> Outpu_Channels_Setup::getAvailableMsgsEnabled(QString chName)
{
    int index = Default_Channels_config::channelList.indexOf(chName);
    if (index == -1)
        return QList<bool>();

    return outputChannels[index].getAvailableMsgsEnabled();
}

bool Outpu_Channels_Setup::getSetupReceivedFlag()
{
    bool result = true;

    foreach (bool flag, chSetupReceivedFlag) {
        if(!flag)
            result = false;
    }

    return result;
}

void Outpu_Channels_Setup::setSetupReceivedFlag(QString chName, bool value)
{
    int index = Default_Channels_config::channelList.indexOf(chName);
    if (index == -1)
        return;

    chSetupReceivedFlag[index] = value;
}

bool Outpu_Channels_Setup::isAlarmOutputEnabled(QString chName) {

    QString alarmEnabledString = getChannelAlarmMsgType(chName);

    if(alarmEnabledString == "ON")
        return true;
    else
        return false;
}

void Outpu_Channels_Setup::getDefaults()
{
    for(int i = 0; i < outputChannels.length(); i++)
        outputChannels[i].getDefaults();
    nmeaBauds.getDefaults();

    nmeaAlrTypes.getDefaults();
}
