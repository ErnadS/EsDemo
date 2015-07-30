#ifndef SINGLECHANNELSETUP_H
#define SINGLECHANNELSETUP_H

#include "sing_ch_sing_msg_s.h"
#include "default_channels_config.h"

class SingleChannelSetup
{
    int channelBaudRate;
    QString channelname;
    QList<Sing_Ch_Sing_Msg_S> channelMsgs;

    void readSetup();
    void writeSetup();
public:
    SingleChannelSetup();
    SingleChannelSetup(int channelBaudRate, QString channelname);

    QList<QString> getMsgsTypes();
    QList<bool> getMsgsAllowed();
    QList<bool> getMsgsEnabled();

    QList<QString> getAvailableMsgsTypes();
    QList<bool> getAvailableMsgsEnabled();

    void setMsgsEnabled(QList<QString> msgTypes, QList<bool> newEnabled);
    void setMsgsEnabled(QString msgTypes, bool newEnabled);

    int getChannelBaudRate() const;
    void setChannelBaudRate(int value);

    bool isAlarmOutputEnabled();


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // SINGLECHANNELSETUP_H
