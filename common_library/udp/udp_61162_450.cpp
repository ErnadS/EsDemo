#include "udp_61162_450.h"
#include "utility/crc8.h"
#include "configuration/system_setup.h"
#include "configuration/system_configuration.h"

// static UDP group names:
const char * UDP_61162_450::multicastGroupName[] = {"MISC", "TGTD", "SATD", "NAVD", "VDRD", "RCOM", "TIME", "PROP"};


int UDP_61162_450::groupNameToIndex(QString groupName) {
    if(groupName == "MISC")
        return MULTICAST_GROUP_MISC;
    else if(groupName == "TGTD")
        return MULTICAST_GROUP_TGTD;
    else if(groupName == "SATD")
        return MULTICAST_GROUP_SATD;
    else if(groupName == "NAVD")
        return MULTICAST_GROUP_NAVD;
    else if(groupName == "VDRD")
        return MULTICAST_GROUP_VDRD;
    else if(groupName == "RCOM")
        return MULTICAST_GROUP_RCOM;
    else if(groupName == "TIME")
        return MULTICAST_GROUP_TIME;
    else if(groupName == "PROP")
        return MULTICAST_GROUP_PROP;

    qDebug() << "!!! ERROR groupName: " << groupName;
    return MULTICAST_GROUP_NAVD; // should never ...
}

QString UDP_61162_450::groupIndexToName(int nIndex) {
    if (nIndex >= 0 && nIndex < 8)
        return multicastGroupName[nIndex];

    qDebug() << "!!! Error groupIndexToName(). Index = " + QString::number(nIndex);

    return "NAVD"; // never ....
}

bool UDP_61162_450::init()
{
    m_nUdpSendingMsgIndex = 0; // UDP standard 61162-450, messages has increasing index from 0 to 999
    udpMulticastConfig.init();
    initUdpMulticast();

    firstStart = true;
    return true;  // TODO
}

void UDP_61162_450::initUdpMulticast()
{
    recalculateGroupIpAndPort();

    udpSocket = new QUdpSocket(this);  // !!! HERE IS A PROBLEM: "QObject: Cannot create children for a parent that is in a different thread."
    udpSocket->bind(QHostAddress::AnyIPv4, udpPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

////////////////////////////////////////////////////////////////////////////
// E.g. if group is "NAVD" (3) => ID= 239.192.0.4 and port = 60004
////////////////////////////////////////////////////////////////////////////
void UDP_61162_450::recalculateGroupIpAndPort() {
    QString groupName;

    if(SystemSetup::getInstance()->getSystemType() == "JB_70")
        groupName = SystemSetup::getInstance()->Jb70Setup.getGroup();
    else
        groupName = SystemSetup::getInstance()->CuM001Setup.getGroup();

    int nGroupIndex = groupNameToIndex(groupName);

    QString udpIp = "239.192.0." + QString::number((nGroupIndex + 1));
    groupAddress = QHostAddress(udpIp);
    udpPort = 60001 + nGroupIndex;
}

// used if group has been changed
void UDP_61162_450::updateUdpGroup()
{
    udpSocket->close();

    recalculateGroupIpAndPort();

    udpSocket->bind(udpPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);
    udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
}

// Datagrams starts with "UdPbC<null>" if msg format is ASCII (TODO: read standard, can we use UTF8?)
void UDP_61162_450::processPendingDatagrams()
{
    QString strTest;
    QString strMsg;

    if(udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;

        if(firstStart)
        {
            while(udpSocket->hasPendingDatagrams())
            {
                datagram.resize(udpSocket->pendingDatagramSize());
                udpSocket->readDatagram(datagram.data(), datagram.size());
            }
            firstStart = false;
            return;
        }

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        strTest = QString::fromLatin1(datagram.data());

        if (strTest == "UdPbC") {
            // qDebug() << "Rec. UDP ASCII: " << strTest;
            strMsg = QString::fromLatin1(&(datagram.data()[6])); // Substring of 6 (after null)
            // qDebug() << "Msg: " << strMsg;
            UdpMulticastGroupMsg* udpMulticastGroupMsg = UdpMulticastParser::parseUdpAsciMsg(strMsg);
            //UdpMulticastGroupMsg* udpMulticastGroupMsg = new UdpMulticastGroupMsg();
/*
            if (!udpMulticastGroupMsg->bValid) {
                qDebug() << "INVALID UDP MSG \r\n";

                foreach (UdpMulticastSingleMsg* single, udpMulticastGroupMsg->msgsList)
                {
                   if (single->nmeaMessage != NULL)
                   {

                       delete single->nmeaMessage;
                       single->nmeaMessage = NULL;
                   }
                }

                delete udpMulticastGroupMsg;
                return;
            }
*/
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // REMOVE MESSAGES WITH WITH WRONG DESTINATION
            if((udpMulticastGroupMsg->msgsList[0]->udpDestinationTag !=  NULL) &&
                     (udpMulticastGroupMsg->msgsList[0]->udpDestinationTag->getTag() !=
                      SystemConfiguration::getSource()))
            {
                foreach (UdpMulticastSingleMsg* single, udpMulticastGroupMsg->msgsList)
                {
                   if (single->nmeaMessage != NULL)
                   {
                       delete single->nmeaMessage;
                       single->nmeaMessage = NULL;
                   }
                }

                delete udpMulticastGroupMsg;
                return;
            }
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SYSTEM_JB70
            else if ((udpMulticastGroupMsg->msgsList[0]->udpSourceTag->getTag() != "SK1111")&&((udpMulticastGroupMsg->msgsList[0]->udpDestinationTag == NULL) || (udpMulticastGroupMsg->msgsList[0]->udpDestinationTag->getTag() == NULL))) {  // Remove if Main unit and msg is without destination
                foreach (UdpMulticastSingleMsg* single, udpMulticastGroupMsg->msgsList)
                {
                   if (single->nmeaMessage != NULL)
                   {
                       delete single->nmeaMessage;
                       single->nmeaMessage = NULL;
                   }
                }

                delete udpMulticastGroupMsg;
                return;
            }
#else
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // REMOVE MESSAGES WITH WRONG SOURCE
            if((udpMulticastGroupMsg->msgsList[0]->udpSourceTag->getTag() != "SK1111") &&
                     (udpMulticastGroupMsg->msgsList[0]->udpSourceTag->getTag() !=
                      SystemConfiguration::getDestination()))
            {
                foreach (UdpMulticastSingleMsg* single, udpMulticastGroupMsg->msgsList)
                {
                   if (single->nmeaMessage != NULL)
                   {
                       delete single->nmeaMessage;
                       single->nmeaMessage = NULL;
                   }
                }

                delete udpMulticastGroupMsg;
                return;
            }
#endif
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // If message from ServiceSoftware
            if (udpMulticastGroupMsg->msgsList[0]->udpSourceTag->getTag() == "SK1111") {
                //qDebug() << "UDP msg from Service Software";
            }




            ///////////////////////////////////////////////
            emit sigHandleUdpMulticast(udpMulticastGroupMsg);
        }
    }
}

qint64 UDP_61162_450::sendMulticastMsg(QByteArray array) {
    //qDebug() << "Group: " << groupAddress << " Port: " << udpPort;
    return udpSocket->writeDatagram(array, groupAddress, udpPort);//array);
}

