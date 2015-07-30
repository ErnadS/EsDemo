#ifndef IP_HANDLER_H
#define IP_HANDLER_H

#include <QList>
#include <QNetworkInterface>

#include "netinterface.h"

class IP_handler
{
public:
    // constructor is private. Use e.g. IP_handler::getInstance();
    static IP_handler* getInstance(); // get a object


    void readIterfaces();
    bool saveInterface(NetInterface* eth0, NetInterface* eth1);
    bool saveInterface();

    bool createDefaultInterfaces(QString systemType);
    bool checkConnection();

    NetInterface eth0_interface;
    NetInterface eth1_interface;

private:
    IP_handler();   // constructor is private
};

#endif // IP_HANDLER_H
