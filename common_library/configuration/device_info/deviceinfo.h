#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>

class DeviceInfo
{
    static QString deviceType;
    static QString vendorID;
    static QString modelCode;
    static QString hardwareRevision;

public:
    DeviceInfo();

    static QString getDeviceType();
    static void setDeviceType(const QString &value);

    static QString getVendorID();
    static void setVendorID(const QString &value);

    //static QString getUniqueIdentifier();
    //static void setUniqueIdentifier(const QString &value);

    static QString getManufacturerSerialNumber();
    static void setManufacturerSerialNumber(const QString &value);

    static QString getModelCode();
    static void setModelCode(const QString &value);

    static QString getSoftwareRevision();
    //static void setSoftwareRevision(const QString &value);

    static QString getHardwareRevision();
    static void setHardwareRevision(const QString &value);
};

#endif // DEVICEINFO_H
