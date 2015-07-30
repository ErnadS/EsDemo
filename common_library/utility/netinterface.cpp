#include "netinterface.h"
#include <QStringList>
#include <QBitArray>
#include <QDebug>

NetInterface::NetInterface()
{
    isNULL = true;
}

void NetInterface::setInterface(QString humanReadableName, QString ipAddress, QString netmask, QString, QString macAddress) {
    isNULL = false;

    this->humanReadableName = humanReadableName;
    this->ipAddress = ipAddress;
    this->netmask = netmask;
    this->defGateway = getDefoultGteway();
    this->macAddress = macAddress;
}

bool NetInterface::isNull() {
    return isNULL;
}

void NetInterface::setInterfaceIp(QString ipAddress)
{
    this->ipAddress = ipAddress;
}

QString NetInterface::getDefoultGteway()
{
    QString result = "";

    QStringList listIP = ipAddress.split(".");
    QStringList listNetmask = netmask.split(".");

    for(int i = 0; i < listIP.length() - 1; i++)
    {
        int intChunkIP = listIP[i].toInt();
        int intChunkNetmask = listNetmask[i].toInt();

        QBitArray chunkIP(8);
        QBitArray chunkNetmask(8);
        QBitArray chunkDefault(8);

        for(int j = 0; j < 8; j++)
        {
            chunkIP[j] = intChunkIP%2;
            chunkNetmask[j] = intChunkNetmask%2;

            intChunkIP = intChunkIP/2;
            intChunkNetmask = intChunkNetmask/2;
        }

        chunkDefault = chunkIP & chunkNetmask;
        int intChunkDefault = 0;
        int powTwo = 1;
        for(int j = 0; j < 8; j++)
        {
            if(chunkDefault[j])
                intChunkDefault += powTwo;

            powTwo *= 2;
        }

        result += QString::number(intChunkDefault) + ".";
    }
    result += "1";

    return result;
}

