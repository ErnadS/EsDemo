#ifndef NMEA_USE_TWO_DECIMALS_S_H
#define NMEA_USE_TWO_DECIMALS_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class NMEA_Use_Two_Decimals_S : public QObject
{
    Q_OBJECT

    QString channelName;
    bool useTwoDecimals;

    Q_PROPERTY(QString channelName READ getChannelName WRITE setChannelName)
    Q_PROPERTY(bool useTwoDecimals      READ getUseTwoDecimals WRITE setUseTwoDecimals)

public:
    explicit NMEA_Use_Two_Decimals_S(QObject *parent = 0);

    NMEA_Use_Two_Decimals_S(QString channelName, int useTwoDecimals);
    NMEA_Use_Two_Decimals_S(const NMEA_Use_Two_Decimals_S& originalValue);
    NMEA_Use_Two_Decimals_S& operator = (const NMEA_Use_Two_Decimals_S &newValue);


    QString getChannelName() const;
    void setChannelName(const QString &value);

    bool getUseTwoDecimals() const;
    void setUseTwoDecimals(bool value);

signals:

public slots:

};

#endif // NMEA_USE_TWO_DECIMALS_S_H
