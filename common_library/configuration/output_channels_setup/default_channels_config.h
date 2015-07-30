#ifndef DEFAULT_CHANNELS_CONFIG_H
#define DEFAULT_CHANNELS_CONFIG_H

#include <QString>
#include <QList>

class Default_Channels_config
{
    Default_Channels_config();

public:

    static QList<QString> channelList;
    static QList<QString> typeList;
    static QList<QString> alarmMsgList;

    static QList<QString> getDefaultTypes();
    static QList<bool> getDefaultAllowed(QString channelName);
    static QList<bool> getDefaultEnabled(QString channelName);
};

#endif // DEFAULT_CHANNELS_CONFIG_H
