#ifndef JB70_SETUP_S_H
#define JB70_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class JB70_Setup_S : public QObject
{
    Q_OBJECT

    QString ipAddress;
    QString localID;
    QString group;
    QString alarmID;
    QString unitName;
    quint32 serialNumber;


    Q_PROPERTY(QString ipAddress READ getIpAddress  WRITE setIpAddress)
    Q_PROPERTY(QString localID   READ getLocalID    WRITE setLocalID)
    Q_PROPERTY(QString group     READ getGroup      WRITE setGroup)
    Q_PROPERTY(QString alarmID   READ getAlarmID    WRITE setAlarmID)
    Q_PROPERTY(QString unitName  READ getUnitName   WRITE setUnitName)
    Q_PROPERTY(quint32 serialNumber  READ getSerialNumber       WRITE setSerialNumber)

public:
    explicit JB70_Setup_S(QObject *parent = 0);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

    QString getLocalID() const;
    void setLocalID(const QString &value);

    QString getGroup() const;
    void setGroup(const QString &value);

    QString getAlarmID() const;
    void setAlarmID(QString value);

    QString getUnitName() const;
    void setUnitName(const QString &value);

    quint32 getSerialNumber() const;
    void setSerialNumber(quint32 value);

signals:

public slots:

};

#endif // JB70_SETUP_S_H
