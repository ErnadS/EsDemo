#include "ip_handler.h"

#include <QFile>
#include <QTextStream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


IP_handler* thisObject;

// Private constructor
IP_handler::IP_handler()
{
}

IP_handler* IP_handler:: getInstance() {
    if (thisObject == NULL)
    {
        thisObject = new IP_handler();
        thisObject->readIterfaces();
    }

    return thisObject;
}

void IP_handler::readIterfaces() {
    QNetworkInterface eth0Interface = QNetworkInterface::interfaceFromName("eth0");
    if (eth0Interface.isValid()) {
        QList<QNetworkAddressEntry> entries = eth0Interface.addressEntries();
        if (!entries.isEmpty()) {
            QNetworkAddressEntry entry = entries.first();
            QHostAddress ip = entry.ip();

            if (ip.toIPv4Address())  {
                QHostAddress netmask = entry.netmask();
                QHostAddress broadcast = entry.broadcast();
                qDebug() << "eth0, netmask: " << netmask.toString() << ", broadcast: " << broadcast.toString();

                // Note: cannot get default gateway from QT???
                eth0_interface.setInterface("eth0", ip.toString(), netmask.toString(), "", eth0Interface.hardwareAddress());
            }
        }
    }

    QNetworkInterface eth1Interface = QNetworkInterface::interfaceFromName("eth1");
    if (eth1Interface.isValid()) {
        QList<QNetworkAddressEntry> entries = eth1Interface.addressEntries();
        if (!entries.isEmpty()) {
            QNetworkAddressEntry entry = entries.first();
            QHostAddress ip = entry.ip();

            if (ip.toIPv4Address())  {
                QHostAddress netmask = entry.netmask();
                QHostAddress broadcast = entry.broadcast();
                // qDebug() << "eth0, netmask: " << netmask.toString() << ", broadcast: " << broadcast.toString();

                // Note: cannot get default gateway from QT???
                eth1_interface.setInterface("eth0", ip.toString(), netmask.toString(), "", eth1Interface.hardwareAddress());
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// Save configuration to "/etc/networking/interfaces" and restart ethernet
/////////////////////////////////////////////////////////////////////////////////////
bool IP_handler::saveInterface(NetInterface* eth0, NetInterface* eth1) {
    //QFile file( "/etc/network/interfaces" );

    bool writegateway = true;

    int fdSerialize1 = open("/etc/network/interfaces", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if(fdSerialize1 == -1)
        return false;

    char temp[100];

    try
    {
        sprintf(temp, "%s", "#Skipper\n\n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s", "auto lo\niface lo inet loopback\n\n\n");
        write(fdSerialize1, temp, strlen(temp));


        //////////////////////////////////////////////////
        // eth0
        //////////////////////////////////////////////////
        if (!eth0->isNull()) {
            sprintf(temp, "%s", "auto eth0 \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s", "iface eth0 inet static \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "address ", (eth0->ipAddress).toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "netmask ", (eth0->netmask).toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "gateway ", (eth0->defGateway).toLatin1().data(), "\n\n\n");
            write(fdSerialize1, temp, strlen(temp));

            writegateway = false;
        }


        //////////////////////////////////////////////////
        // eth1
        //////////////////////////////////////////////////
        if (!eth1->isNull()) {
            sprintf(temp, "%s", "auto eth1 \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s", "iface eth1 inet static \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "address ", (eth1->ipAddress).toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "netmask ", (eth1->netmask).toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            if(writegateway) // Can't have two default gateways (?), default gateway is optional anyway, so should work without it (?).
                sprintf(temp, "%s%s%s", "gateway ", (eth1->defGateway).toLatin1().data(), "\n\n\n");
            write(fdSerialize1, temp, strlen(temp));
        }

        #if defined(Q_OS_WIN)
        {
            _commit(fdSerialize1);
        }
        #else
        {
            fsync(fdSerialize1);
        }
        #endif

        close(fdSerialize1);

        system("/etc/init.d/S40network restart");

        return true;
    }
    catch (int e)
    {
        close(fdSerialize1);
        qDebug() << "Error in writing to /etc/network/interfaces: " << e;
        return false;
    }

    return false;
}

bool IP_handler::saveInterface()
{
    return saveInterface(&eth0_interface, &eth1_interface);
}

bool IP_handler::createDefaultInterfaces(QString systemType)
{
    QString eth0_Address = "172.16.1.98";
    QString eth0_Netmask = "255.255.255.0";
    QString eth0_Gateway = "172.16.1.1";

    QString eth1_Address = "172.16.2.98 ";
    QString eth1_Netmask = "255.255.255.0";
    QString eth1_Gateway = "172.16.2.1";

    bool writeBoth = true;

    if(systemType != "JB_70")
    {
        eth1_Address = "172.16.1.99 ";
        eth1_Gateway = "172.16.1.1";
        writeBoth = false;
    }


    int fdSerialize1 = open("/etc/network/interfaces", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if(fdSerialize1 == -1)
        return false;

    char temp[100];

    try
    {
        sprintf(temp, "%s", "#Skipper\n\n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s", "auto lo\niface lo inet loopback\n\n\n");
        write(fdSerialize1, temp, strlen(temp));


        //////////////////////////////////////////////////
        // eth0
        //////////////////////////////////////////////////
        if (writeBoth) {
            sprintf(temp, "%s", "auto eth0 \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s", "iface eth0 inet static \n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "address ", eth0_Address.toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "netmask ", eth0_Netmask.toLatin1().data(), "\n");
            write(fdSerialize1, temp, strlen(temp));

            sprintf(temp, "%s%s%s", "gateway ", eth0_Gateway.toLatin1().data(), "\n\n\n");
            write(fdSerialize1, temp, strlen(temp));
        }


        //////////////////////////////////////////////////
        // eth1
        //////////////////////////////////////////////////
        sprintf(temp, "%s", "auto eth1 \n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s", "iface eth1 inet static \n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s%s%s", "address ", eth1_Address.toLatin1().data(), "\n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s%s%s", "netmask ", eth1_Netmask.toLatin1().data(), "\n");
        write(fdSerialize1, temp, strlen(temp));

        sprintf(temp, "%s%s%s", "gateway ", eth1_Gateway.toLatin1().data(), "\n\n\n");
        write(fdSerialize1, temp, strlen(temp));
        //////////////////////////////////////////////////

        #if defined(Q_OS_WIN)
        {
            _commit(fdSerialize1);
        }
        #else
        {
            fsync(fdSerialize1);
        }
        #endif

        close(fdSerialize1);

        system("/etc/init.d/S40network restart");

        return true;
    }
    catch (int e)
    {
        close(fdSerialize1);
        qDebug() << "Error in writing to /etc/network/interfaces: " << e;
        return false;
    }

    return false;
}

bool IP_handler::checkConnection()
{
    return true;
}

/*
  QList<QString> possibleMatches;

    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
   // QNetworkInterface* network = new QNetworkInterface();

    if ( !ifaces.isEmpty() )
    {
        foreach(QNetworkInterface interface, ifaces) {
            unsigned int flags = interface.flags();
            bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
            bool isP2P = (bool)(flags & QNetworkInterface::IsPointToPoint);
            bool isRunning = (bool)(flags & QNetworkInterface::IsRunning);

            if (interface.humanReadableName() == "eth0") {
                macAddress = interface.hardwareAddress();
                qDebug() << "eth0, mac: " << macAddress;
            } else if (interface.humanReadableName() == "eth1") {
                macAddress = interface.hardwareAddress();
                qDebug() << "eth1, mac: " << macAddress;
            }

            // If this interface isn't running, we don't care about it
            if ( !isRunning ) continue;
            // We only want valid interfaces that aren't loopback/virtual and not point to point
            if ( !ifaces[i].isValid() || isLoopback || isP2P ) continue;
            QList<QHostAddress> addresses = ifaces[i].allAddresses();
            for(int a=0; a < addresses.size(); a++)
            {
                // Ignore local host
                if ( addresses[a] == QHostAddress::LocalHost ) continue;

                // Ignore non-ipv4 addresses
                if ( !addresses[a].toIPv4Address() ) continue;

                QString ip = addresses[a].toString();
                if ( ip.isEmpty() ) continue;
                bool foundMatch = false;
                for (int j=0; j < possibleMatches.size(); j++) if ( ip == possibleMatches[j] ) { foundMatch = true; break; }
                if ( !foundMatch ) { possibleMatches.push_back( ip ); qDebug() << "possible address: " << ifaces[i].humanReadableName() << "->" << ip; }
            }
        }
    }*/



/*
char dhcpLinux_read(GW_DHCP* dhcp) {
    int i = 0;
    int maxSize = 500;
    char buff[maxSize];

    FILE * hFile;
    hFile = fopen(DHCP_LIN_CONFIG_PATH, "r");
    if (hFile == NULL) {
        return 0;
    }

    int c;
    while ((c = fgetc(hFile)) != EOF && i < maxSize) {
        buff[i++] = (char) c;
    }
    buff[i] = 0;

    if (dhcpLinux_updateStructFromBuffer(buff, dhcp) != 0) {
        fclose(hFile);

        strcpy(dhcp->dhcp, "0");
        strcpy(dhcp->ip, "192.168.1.222");
        strcpy(dhcp->sm, "255.255.255.0");
        strcpy(dhcp->gat, "192.168.1.1");
        strcpy(dhcp->dns, "192.168.1.1");
        dhcpLinux_save(*dhcp);
    } else {
        fclose(hFile);
    }

    return 1;
}*/

