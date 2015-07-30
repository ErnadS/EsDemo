#ifndef NETINTERFACE_H
#define NETINTERFACE_H

#include <QString>


class NetInterface
{
public:
    NetInterface();  // "isUsed" is "false" after creatin object. It becoms "true" after "setInterface"

    void setInterface(QString humanReadableName, QString ipAddress, QString netmask, QString defGateway, QString macAddress);



    QString         humanReadableName;  // "eth0" or "eth1"
    QString         ipAddress;
    QString         netmask;
    QString         defGateway;         // note: Qt does not have way to find it?
    QString         macAddress;


    bool isNull();

    void setInterfaceIp(QString ipAddress);

    QString getDefoultGteway();


private:
    bool isNULL;   // true if hardware has this inteface


};

#endif // NETINTERFACE_H
