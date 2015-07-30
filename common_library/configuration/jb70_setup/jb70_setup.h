#ifndef JB70_SETUP_H
#define JB70_SETUP_H

#include "jb70_setup_s.h"

class JB70_Setup
{
    JB70_Setup_S Jb70Setup;

    bool setupReceivedFlag;

    QString oldLocalId;
    QString softwareVersion;

    QString systemType;

    void readSetup();
    void writeSetup();
public:
    JB70_Setup();

    void setJb70(QString ipAddress, QString localID, QString group, QString alarmID, quint32 serialNum);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

    void changeIpAddress(QString newIp = "UseExisting");

    QString getLocalID() const;
    QString getOldLocalID() const;
    void setLocalID(const QString &value);

    QString getSoftwareVersion() const;
    void setSoftwareVersion(const QString& value);

    QString getGroup() const;
    void setGroup(const QString &value);

    QString getAlarmID() const;
    void setAlarmID(QString value);

    bool getSetupReceivedFlag();
    void setSetupReceivedFlag(bool value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);

    QString getUnitName() const;
    void setUnitName(const QString &value);

    quint32 getSerialNumber() const;
    void setSerialNumber(quint32 value);
    void getDefaults(int level = 0);
};


#endif // JB70_SETUP_H
