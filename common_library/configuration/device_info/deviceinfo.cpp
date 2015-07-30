#include "deviceinfo.h"

#ifdef SYSTEM_JB70
    QString DeviceInfo::deviceType = "VD2";
    QString DeviceInfo::modelCode = "JB70D2";
    QString DeviceInfo::hardwareRevision = "AX";
#else
    QString DeviceInfo::deviceType = "II";
    QString DeviceInfo::modelCode = "CU-M001";
    QString DeviceInfo::hardwareRevision = "SA";
#endif

QString DeviceInfo::vendorID = "SKP";


DeviceInfo::DeviceInfo()
{
}
QString DeviceInfo::getHardwareRevision()
{
    return hardwareRevision;
}

void DeviceInfo::setHardwareRevision(const QString &value)
{
    hardwareRevision = value;
}

QString DeviceInfo::getSoftwareRevision()
{
    return APP_VERSION;
}

QString DeviceInfo::getModelCode()
{
    return modelCode;
}

void DeviceInfo::setModelCode(const QString &value)
{
    modelCode = value;
}

QString DeviceInfo::getVendorID()
{
    return vendorID;
}

void DeviceInfo::setVendorID(const QString &value)
{
    vendorID = value;
}

QString DeviceInfo::getDeviceType()
{
    return deviceType;
}

void DeviceInfo::setDeviceType(const QString &value)
{
    deviceType = value;
}

