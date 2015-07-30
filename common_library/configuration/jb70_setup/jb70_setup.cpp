#include "jb70_setup.h"
#include "utility/ip_handler.h"
#ifdef SYSTEM_JB70
    #include "drivers/uniqideeprom.h"
#endif

void JB70_Setup::getDefaults(int level)
{
    Jb70Setup.setAlarmID("AS0101");
    if(level >= 2)
    {
        Jb70Setup.setUnitName("JB70DL2");
        Jb70Setup.setLocalID("VD0101");
        Jb70Setup.setGroup("NAVD");

        if(level != 7)
        {
            Jb70Setup.setIpAddress("172.16.1.101");
            if(systemType == "JB_70")
                changeIpAddress();
        }
    }

    writeSetup();
}

void JB70_Setup::readSetup()
{
    if (!SerializationController::Deserialize(Jb70Setup, "jb70_setup", "/setup_files/", false))
    {
        getDefaults(7);
    }

    if(systemType == "JB_70")
    {
        if(!IP_handler:: getInstance()->checkConnection())
        {
            IP_handler:: getInstance()->createDefaultInterfaces("JB_70");
            IP_handler:: getInstance()->readIterfaces();
        }

        NetInterface* interface;
           if(!IP_handler:: getInstance()->eth0_interface.isNull())
               interface = &IP_handler:: getInstance()->eth0_interface;
           else
               interface = &IP_handler:: getInstance()->eth1_interface;
        Jb70Setup.setIpAddress(interface->ipAddress);
    }


    oldLocalId = Jb70Setup.getLocalID();
}

void JB70_Setup::writeSetup()
{
    SerializationController::Serialize(Jb70Setup, "jb70_setup", "/setup_files/", false);
}

JB70_Setup::JB70_Setup()
{
#ifdef SYSTEM_JB70
    systemType = "JB_70";
#else
    systemType = "CU_M001";
#endif
    readSetup();
    setupReceivedFlag = false;

    softwareVersion = APP_VERSION;
}

void JB70_Setup::setJb70(QString ipAddress, QString localID, QString group, QString alarmID, quint32 serialNum)
{
    Jb70Setup.setIpAddress(ipAddress);
    Jb70Setup.setLocalID(localID);
    Jb70Setup.setGroup(group);
    Jb70Setup.setAlarmID(alarmID);
    Jb70Setup.setSerialNumber(serialNum);

    setupReceivedFlag = true;

    writeSetup();
}

QString JB70_Setup::getIpAddress() const
{
    return Jb70Setup.getIpAddress();
}

void JB70_Setup::setIpAddress(const QString &value)
{
    Jb70Setup.setIpAddress(value);
    writeSetup();
}

void JB70_Setup::changeIpAddress(QString newIp)
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

QString JB70_Setup::getLocalID() const
{
    return Jb70Setup.getLocalID();
}

QString JB70_Setup::getOldLocalID() const
{
    return oldLocalId;
}

void JB70_Setup::setLocalID(const QString &value)
{
    oldLocalId = Jb70Setup.getLocalID();
    Jb70Setup.setLocalID(value);
    writeSetup();
}

QString JB70_Setup::getSoftwareVersion() const
{
    return softwareVersion;
}

void JB70_Setup::setSoftwareVersion(const QString& value)
{
    softwareVersion = value;
}


QString JB70_Setup::getGroup() const
{
    return Jb70Setup.getGroup();
}

void JB70_Setup::setGroup(const QString &value)
{
    Jb70Setup.setGroup(value);
    writeSetup();
}

QString JB70_Setup::getAlarmID() const
{
    return Jb70Setup.getAlarmID();
}

void JB70_Setup::setAlarmID(QString value)
{
    Jb70Setup.setAlarmID(value);
    writeSetup();
}

bool JB70_Setup::getSetupReceivedFlag()
{
    return setupReceivedFlag;
}

void JB70_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}

bool JB70_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(Jb70Setup, "jb70_setup" + fileSuffix, "/setup_files/saved_configs/", false);
}

bool JB70_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(Jb70Setup, "jb70_setup" + fileSuffix, "/setup_files/saved_configs/", false);
}

quint32 JB70_Setup::getSerialNumber() const
{
    return Jb70Setup.getSerialNumber();
}

void JB70_Setup::setSerialNumber(quint32 value)
{
    Jb70Setup.setSerialNumber(value);
    writeSetup();
}

QString JB70_Setup::getUnitName() const
{
    return Jb70Setup.getUnitName();
}

void JB70_Setup::setUnitName(const QString &value)
{
    Jb70Setup.setUnitName(value);
    writeSetup();
}
