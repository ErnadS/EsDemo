#ifndef SYSTEMCONFIGURATION_H
#define SYSTEMCONFIGURATION_H

#include <QString>
#include "QStringList"

#define SYSTEM_DL1              1
#define SYSTEM_DL2_MASTER       2
#define SYSTEM_DL2_SLAVE        3
#define SYSTEM_DL2              4


class SystemConfiguration
{
    
public:
    SystemConfiguration();
    // Probably should not be a static. One class should be owner of this object
    static QString getSourceTalker();   // e.g. "VD"
    static quint16 getSourceId();       // from 0 to 9999 (e.g. "12" (when id = 0012))
    static QString getSource();         // Talker + sourceID (e.g. "VD0221")
    static QString getIp();

    static QString getDestination();    // For display

    static quint8 getSystemId();

    static QString systemType;

    static QString getLocalID();
    static QString getSystemType();
    static void setSystemType(const QString &value);

    static int getNumberOfDecimals();

private:

};

#endif // SYSTEMCONFIGURATION_H
