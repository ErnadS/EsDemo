#ifndef ALARMIDS_SETUP_S_H
#define ALARMIDS_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class AlarmIDs_Setup_S : public QObject
{
    Q_OBJECT

    int stwHighAlarmID;
    int stwLowAlarmID;
    int sogHighAlarmID;
    int sogLowAlarmID;

    int systemAlarmID;

    bool useALR;

    int escalationTime;

    Q_PROPERTY(int stwHighAlarmID READ getStwHighAlarmID WRITE setStwHighAlarmID)
    Q_PROPERTY(int stwLowAlarmID  READ getStwLowAlarmID  WRITE setStwLowAlarmID)
    Q_PROPERTY(int sogHighAlarmID READ getSogHighAlarmID WRITE setSogHighAlarmID)
    Q_PROPERTY(int sogLowAlarmID  READ getSogLowAlarmID  WRITE setSogLowAlarmID)
    Q_PROPERTY(int systemAlarmID  READ getSystemAlarmID  WRITE setSystemAlarmID)
    Q_PROPERTY(bool useALR        READ getUseALR         WRITE setUseALR)
    Q_PROPERTY(int escalationTime READ getEscalationTime WRITE setEscalationTime)
public:
    explicit AlarmIDs_Setup_S(QObject *parent = 0);

    int getStwHighAlarmID() const;
    void setStwHighAlarmID(int value);

    int getStwLowAlarmID() const;
    void setStwLowAlarmID(int value);

    int getSogHighAlarmID() const;
    void setSogHighAlarmID(int value);

    int getSogLowAlarmID() const;
    void setSogLowAlarmID(int value);

    int getSystemAlarmID() const;
    void setSystemAlarmID(int value);

    bool getUseALR() const;
    void setUseALR(bool value);

    int getEscalationTime() const;
    void setEscalationTime(int value);

signals:

public slots:

};

#endif // ALARMIDS_SETUP_S_H
