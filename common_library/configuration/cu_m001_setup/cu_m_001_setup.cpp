#include "cu_m_001_setup.h"
#include "utility/ip_handler.h"


bool CU_M_001_Setup::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void CU_M_001_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}
void CU_M_001_Setup::getDefaults(int level)
{
    CuM001Setup.setScreenOrientation(1);
    CuM001Setup.setSystemType(1);
    CuM001Setup.setRemoteDimmDdc("RX");
    CuM001Setup.setSeccondSystemType(0);
    CuM001Setup.setSeccondystemMenu(false);
    CuM001Setup.setThirdSystemType(0);
    CuM001Setup.setThirdSystemMenu(false);
    CuM001Setup.setSoftwareUpdate("Not available.");
    CuM001Setup.setUnitsDepth(0);
    CuM001Setup.setUnitsSpeed(0);
    CuM001Setup.setUnitName("Display");
    if(level >= 2)
    {
        CuM001Setup.setLocalID("II0102");
        CuM001Setup.setPairedID("VD0101");
        CuM001Setup.setGroup("NAVD");
        if(level != 7)
        {
            CuM001Setup.setIpAddress("172.16.1.102");

            if(systemType != "JB_70")
                changeIpAddress();
        }
    }

    writeSetup();
}

void CU_M_001_Setup::readSetup()
{
    if (!SerializationController::Deserialize(CuM001Setup, "cu_m_001_setup", "/setup_files/", false))
    {
        /*CuM001Setup.setIpAddress("192.168.0.99");
        CuM001Setup.setLocalID("II0102");
        CuM001Setup.setPairedID("VD0101");
        CuM001Setup.setGroup("NAVD");*/
        getDefaults(7);
    }
    if(systemType != "JB_70")
    {
        if(!IP_handler:: getInstance()->checkConnection())
        {
            IP_handler:: getInstance()->createDefaultInterfaces("CU_M001");
            IP_handler:: getInstance()->readIterfaces();
        }

        NetInterface* interface;
           if(!IP_handler:: getInstance()->eth0_interface.isNull())
               interface = &IP_handler:: getInstance()->eth0_interface;
           else
               interface = &IP_handler:: getInstance()->eth1_interface;
        CuM001Setup.setIpAddress(interface->ipAddress);
    }
}

void CU_M_001_Setup::writeSetup()
{
    SerializationController::Serialize(CuM001Setup, "cu_m_001_setup", "/setup_files/", false);
}

void CU_M_001_Setup::changeIpAddress(QString newIp)
{
    QString changeTo;
    if (newIp == "UseExisting")
        changeTo = getIpAddress();
    else
        changeTo = newIp;

    NetInterface* interface;
    if(!IP_handler:: getInstance()->eth0_interface.isNull())
        interface = &IP_handler:: getInstance()->eth0_interface;
    else
        interface = &IP_handler:: getInstance()->eth1_interface;

    if(interface->ipAddress != changeTo)
    {
        interface->setInterfaceIp(changeTo);
        interface->defGateway = interface->getDefoultGteway();
        IP_handler:: getInstance()->saveInterface();
    }
}

bool CU_M_001_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(CuM001Setup, "cu_m_001_setup" + fileSuffix, "/setup_files/saved_configs/", false);
}

bool CU_M_001_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(CuM001Setup, "cu_m_001_setup" + fileSuffix, "/setup_files/saved_configs/", false);
}

CU_M_001_Setup::CU_M_001_Setup()
{
#ifdef SYSTEM_JB70
    systemType = "JB_70";
#else
    systemType = "CU_M001";
#endif
    readSetup();
    setupReceivedFlag = false;
}

void CU_M_001_Setup::setCuM001(int screenOrientation, int systemType, QString ipAddress, QString localID, QString pairedID,
                               QString group, QString remoteDimmDdc, int seccondSystemType, bool seccondystemMenu,
                               int thirdSystemType, bool thirdSystemMenu, QString softwareUpdate, int vesselIndex, int unitsDepth,
                               int unitsSpeed)
{
    CuM001Setup.setScreenOrientation(screenOrientation);
    CuM001Setup.setSystemType(systemType);
    CuM001Setup.setIpAddress(ipAddress);
    CuM001Setup.setLocalID(localID);
    CuM001Setup.setPairedID(pairedID);
    CuM001Setup.setGroup(group);
    CuM001Setup.setRemoteDimmDdc(remoteDimmDdc);
    CuM001Setup.setSeccondSystemType(seccondSystemType);
    CuM001Setup.setSeccondystemMenu(seccondystemMenu);
    CuM001Setup.setThirdSystemType(thirdSystemType);
    CuM001Setup.setThirdSystemMenu(thirdSystemMenu);
    CuM001Setup.setSoftwareUpdate(softwareUpdate);

    CuM001Setup.setVesselIndex(vesselIndex);

    CuM001Setup.setUnitsDepth(unitsDepth);
    CuM001Setup.setUnitsSpeed(unitsSpeed);

    setupReceivedFlag = true;

    writeSetup();
}

int CU_M_001_Setup::getScreenOrientation() const
{
    return CuM001Setup.getScreenOrientation();
}

void CU_M_001_Setup::setScreenOrientation(int value)
{
    CuM001Setup.setScreenOrientation(value);
    writeSetup();
}

int CU_M_001_Setup::getSystemType() const
{
    return CuM001Setup.getSystemType();
}

void CU_M_001_Setup::setSystemType(int value)
{
    CuM001Setup.setSystemType(value);
    writeSetup();
}

QString CU_M_001_Setup::getIpAddress() const
{
    return CuM001Setup.getIpAddress();
}

void CU_M_001_Setup::setIpAddress(const QString &value)
{
    // Should change here
    CuM001Setup.setIpAddress(value);
    writeSetup();
}

QString CU_M_001_Setup::getLocalID() const
{
    return CuM001Setup.getLocalID();
}

void CU_M_001_Setup::setLocalID(const QString &value)
{
    CuM001Setup.setLocalID(value);
    writeSetup();
}

QString CU_M_001_Setup::getPairedID() const
{
    return CuM001Setup.getPairedID();
}

void CU_M_001_Setup::setPairedID(const QString &value)
{
    CuM001Setup.setPairedID(value);
    writeSetup();
}

QString CU_M_001_Setup::getGroup() const
{
    return CuM001Setup.getGroup();
}

void CU_M_001_Setup::setGroup(const QString &value)
{
    CuM001Setup.setGroup(value);
    writeSetup();
}

QString CU_M_001_Setup::getRemoteDimmDdc() const
{
    return CuM001Setup.getRemoteDimmDdc();
}

void CU_M_001_Setup::setRemoteDimmDdc(const QString &value)
{
    CuM001Setup.setRemoteDimmDdc(value);
    writeSetup();
}

int CU_M_001_Setup::getSeccondSystemType() const
{
    return CuM001Setup.getSeccondSystemType();
}

void CU_M_001_Setup::setSeccondSystemType(int value)
{
    CuM001Setup.setSeccondSystemType(value);
    writeSetup();
}

bool CU_M_001_Setup::getSeccondystemMenu() const
{
    return CuM001Setup.getSeccondystemMenu();
}

void CU_M_001_Setup::setSeccondystemMenu(bool value)
{
    CuM001Setup.setSeccondystemMenu(value);
    writeSetup();
}

int CU_M_001_Setup::getThirdSystemType() const
{
    return CuM001Setup.getThirdSystemType();
}

void CU_M_001_Setup::setThirdSystemType(int value)
{
    CuM001Setup.setThirdSystemType(value);
    writeSetup();
}

bool CU_M_001_Setup::getThirdSystemMenu() const
{
    return CuM001Setup.getThirdSystemMenu();
}

void CU_M_001_Setup::setThirdSystemMenu(bool value)
{
    CuM001Setup.setThirdSystemMenu(value);
    writeSetup();
}

QString CU_M_001_Setup::getSoftwareUpdate() const
{
    return CuM001Setup.getSoftwareUpdate();
}

void CU_M_001_Setup::setSoftwareUpdate(const QString &value)
{
    CuM001Setup.setSoftwareUpdate(value);
    writeSetup();
}

int CU_M_001_Setup::getVesselIndex() const
{
    return CuM001Setup.getVesselIndex();
}

void CU_M_001_Setup::setVesselIndex(int value)
{
    CuM001Setup.setVesselIndex(value);
    writeSetup();
}

int CU_M_001_Setup::getUnitsDepth() const
{
    return CuM001Setup.getUnitsDepth();
}

void CU_M_001_Setup::setUnitsDepth(int value)
{
    CuM001Setup.setUnitsDepth(value);
    writeSetup();
}

int CU_M_001_Setup::getUnitsSpeed() const
{
    return CuM001Setup.getUnitsSpeed();
}

void CU_M_001_Setup::setUnitsSpeed(int value)
{
    CuM001Setup.setUnitsSpeed(value);
    writeSetup();
}

QString CU_M_001_Setup::getUnitsDepthString() const
{
    if(getUnitsDepth() == 1)
        return "ftm";
    if(getUnitsDepth() == 2)
        return "ft";
    else
        return "m";

}

QString CU_M_001_Setup::getUnitsSpeedString() const
{
    if(getUnitsSpeed() == 1)
        return "mps";
    if(getUnitsSpeed() == 2)
        return "miph";
    else
        return "kn";
}

int CU_M_001_Setup::getSerialNumber() const
{
    return CuM001Setup.getSerialNumber();
}

void CU_M_001_Setup::setSerialNumber(int value)
{
    CuM001Setup.setSerialNumber(value);
    writeSetup();
}

QString CU_M_001_Setup::getUnitName() const
{
    return CuM001Setup.getUnitName();
}

void CU_M_001_Setup::setUnitName(const QString &value)
{
    CuM001Setup.setUnitName(value);
    writeSetup();
}
