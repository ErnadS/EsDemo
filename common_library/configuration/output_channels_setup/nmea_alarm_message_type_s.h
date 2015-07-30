#ifndef NMEA_ALARM_MESSAGE_TYPE_S_H
#define NMEA_ALARM_MESSAGE_TYPE_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class NMEA_Alarm_Message_Type_S : public QObject
{
    Q_OBJECT

    QString channelName;
    QString channelAlarmMessageType;

    Q_PROPERTY(QString channelName             READ getChannelName             WRITE setChannelName)
    Q_PROPERTY(QString channelAlarmMessageType READ getChannelAlarmMessageType WRITE setChannelAlarmMessageType)

public:
    explicit NMEA_Alarm_Message_Type_S(QObject *parent = 0);

    NMEA_Alarm_Message_Type_S(QString channelName, QString channelAlarmMessageType);
    NMEA_Alarm_Message_Type_S(const NMEA_Alarm_Message_Type_S& originalValue);
    NMEA_Alarm_Message_Type_S& operator = (const NMEA_Alarm_Message_Type_S &newValue);

    QString getChannelName() const;
    void setChannelName(const QString &value);

    QString getChannelAlarmMessageType() const;
    void setChannelAlarmMessageType(const QString &value);

signals:

public slots:

};

#endif // NMEA_ALARM_MESSAGE_TYPE_S_H
