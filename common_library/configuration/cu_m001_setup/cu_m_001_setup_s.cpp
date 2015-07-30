#include "cu_m_001_setup_s.h"


int CU_M_001_Setup_S::getScreenOrientation() const
{
    return screenOrientation;
}

void CU_M_001_Setup_S::setScreenOrientation(int value)
{
    screenOrientation = value;
}

int CU_M_001_Setup_S::getSystemType() const
{
    return systemType;
}

void CU_M_001_Setup_S::setSystemType(int value)
{
    systemType = value;
}

QString CU_M_001_Setup_S::getIpAddress() const
{
    return ipAddress;
}

void CU_M_001_Setup_S::setIpAddress(const QString &value)
{
    ipAddress = value;
}

QString CU_M_001_Setup_S::getLocalID() const
{
    return localID;
}

void CU_M_001_Setup_S::setLocalID(const QString &value)
{
    localID = value;
}

QString CU_M_001_Setup_S::getPairedID() const
{
    return pairedID;
}

void CU_M_001_Setup_S::setPairedID(const QString &value)
{
    pairedID = value;
}

QString CU_M_001_Setup_S::getGroup() const
{
    return group;
}

void CU_M_001_Setup_S::setGroup(const QString &value)
{
    group = value;
}

QString CU_M_001_Setup_S::getRemoteDimmDdc() const
{
    return remoteDimmDdc;
}

void CU_M_001_Setup_S::setRemoteDimmDdc(const QString &value)
{
    remoteDimmDdc = value;
}

int CU_M_001_Setup_S::getSeccondSystemType() const
{
    return seccondSystemType;
}

void CU_M_001_Setup_S::setSeccondSystemType(int value)
{
    seccondSystemType = value;
}

bool CU_M_001_Setup_S::getSeccondystemMenu() const
{
    return seccondystemMenu;
}

void CU_M_001_Setup_S::setSeccondystemMenu(bool value)
{
    seccondystemMenu = value;
}

int CU_M_001_Setup_S::getThirdSystemType() const
{
    return thirdSystemType;
}

void CU_M_001_Setup_S::setThirdSystemType(int value)
{
    thirdSystemType = value;
}

bool CU_M_001_Setup_S::getThirdSystemMenu() const
{
    return thirdSystemMenu;
}

void CU_M_001_Setup_S::setThirdSystemMenu(bool value)
{
    thirdSystemMenu = value;
}

QString CU_M_001_Setup_S::getSoftwareUpdate() const
{
    return softwareUpdate;
}

void CU_M_001_Setup_S::setSoftwareUpdate(const QString &value)
{
    softwareUpdate = value;
}

int CU_M_001_Setup_S::getVesselIndex() const
{
    return vesselIndex;
}

void CU_M_001_Setup_S::setVesselIndex(int value)
{
    vesselIndex = value;
}

int CU_M_001_Setup_S::getUnitsDepth() const
{
    return unitsDepth;
}

void CU_M_001_Setup_S::setUnitsDepth(int value)
{
    unitsDepth = value;
}

int CU_M_001_Setup_S::getUnitsSpeed() const
{
    return unitsSpeed;
}

void CU_M_001_Setup_S::setUnitsSpeed(int value)
{
    unitsSpeed = value;
}

int CU_M_001_Setup_S::getSerialNumber() const
{
    return serialNumber;
}

void CU_M_001_Setup_S::setSerialNumber(int value)
{
    serialNumber = value;
}

QString CU_M_001_Setup_S::getUnitName() const
{
    return unitName;
}

void CU_M_001_Setup_S::setUnitName(const QString &value)
{
    unitName = value;
}


CU_M_001_Setup_S::CU_M_001_Setup_S(QObject *parent) :
    QObject(parent)
{
    vesselIndex = 2;
    unitsDepth = 0;
    unitsSpeed = 0;
}
