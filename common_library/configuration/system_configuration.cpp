#include "system_configuration.h"
#include "utility/ip_handler.h"
#include "system_setup.h"

static quint8 systemId = 2;  // DL2
static QString sourceTalker = "VD";

QString SystemConfiguration::systemType = "JB_70";

QString SystemConfiguration::getSourceTalker()
{
    QString source = getLocalID();

    QString sourceTlk = source.left(2);

    return sourceTlk;
}

quint16 SystemConfiguration::getSourceId()
{
    QString source = getLocalID();
    source.remove(0, 2);

    int sId = source.toInt();

    return sId;
}

QString SystemConfiguration::getSource()
{
    QString strId;
    strId.sprintf("%04d", getSourceId());

    QString source = getSourceTalker() + strId;
    return source;
}

QString SystemConfiguration::getIp() {
    IP_handler* ip_handler = IP_handler::getInstance();

    return ip_handler->eth0_interface.ipAddress;
    // On display use this:
    // return ip_handler->eth1_interface.ipAddress;
}

QString SystemConfiguration::getDestination()
{
    QString destination = SystemSetup::getInstance()->CuM001Setup.getPairedID();// Jb70Setup.getLocalID();

    QString destinationTalker = destination.left(2);

    destination.remove(0,2);

    while (destination.length() < 4)
        destination = "0" + destination;

    destination  = destinationTalker + destination;

    return destination;
}

quint8 SystemConfiguration::getSystemId()
{
    return systemId; // DL2= 2;
}

QString SystemConfiguration::getLocalID()
{
    QString localID = "";
    if(systemType == "JB_70")
        localID = SystemSetup::getInstance()->Jb70Setup.getLocalID();
    else if(systemType == "CU_M001")
        localID = SystemSetup::getInstance()->CuM001Setup.getLocalID();

    return localID;
}

QString SystemConfiguration::getSystemType()
{
    return systemType;
}

void SystemConfiguration::setSystemType(const QString &value)
{
    systemType = value;
}

int SystemConfiguration::getNumberOfDecimals()
{
    return SystemSetup::getInstance()->Dl2Setup.numberOfDecimals();
}
