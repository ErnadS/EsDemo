#ifndef NMEA_BAUD_S_H
#define NMEA_BAUD_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class NMEA_Baud_S : public QObject
{
    Q_OBJECT

    QString channelName;
    int channelBaud;

    Q_PROPERTY(QString channelName READ getChannelName WRITE setChannelName)
    Q_PROPERTY(int channelBaud      READ getChannelBaud WRITE setChannelBaud)

public:
    explicit NMEA_Baud_S(QObject *parent = 0);

    NMEA_Baud_S(QString channelName,int channelBaud);
    NMEA_Baud_S(const NMEA_Baud_S& originalValue);
    NMEA_Baud_S& operator = (const NMEA_Baud_S &newValue);

    QString getChannelName() const;
    void setChannelName(const QString &value);

    int getChannelBaud() const;
    void setChannelBaud(int value);

signals:

public slots:

};

#endif // NMEA_BAUD_S_H
