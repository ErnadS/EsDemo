#ifndef UDP_61162_450_H
#define UDP_61162_450_H

#include "udp_multicast_config.h"
#include <QtNetwork>
#include <QUdpSocket>

#include "udp_multicast_single_msg.h"
#include "udp_multicast_group_msg.h"
#include "udp/tag/udp_source_tag.h"
#include "udp/tag/udp_destination_tag.h"
#include "udp/tag/udp_group_tag.h"

#include "udp_multicast_parser.h"

#define MULTICAST_GROUP_MISC 0
#define MULTICAST_GROUP_TGTD 1
#define MULTICAST_GROUP_SATD 2
#define MULTICAST_GROUP_NAVD 3
#define MULTICAST_GROUP_VDRD 4
#define MULTICAST_GROUP_RCOM 5
#define MULTICAST_GROUP_TIME 6
#define MULTICAST_GROUP_PROP 7

class UDP_61162_450: public QObject
{
    Q_OBJECT

public:
    bool init();
    void updateUdpGroup();
    void recalculateGroupIpAndPort();

    qint64 sendMulticastMsg(QByteArray array);

    static int groupNameToIndex(QString groupName);
    static QString groupIndexToName(int nIndex);

private:
    QUdpSocket *udpSocket;
    UdpMulticastConfig udpMulticastConfig;
    QHostAddress groupAddress;
    quint16 m_nUdpSendingMsgIndex; // counter we are using when sending messages

    quint16 udpPort;

    bool firstStart;

    void initUdpMulticast();

    static const char * multicastGroupName[];


public slots:
    void processPendingDatagrams();

signals:
    void sigHandleUdpMulticast(UdpMulticastGroupMsg* udpMulticastGroupMsg);
};




#endif // UDP_61162_450_H
