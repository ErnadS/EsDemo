#ifndef UDP_MULTICAST_GROUP_MSG_H
#define UDP_MULTICAST_GROUP_MSG_H

#include "udp_multicast_single_msg.h"
#include <QList>

class UdpMulticastGroupMsg
{
public:
    UdpMulticastGroupMsg();
    ~UdpMulticastGroupMsg();

    QList<UdpMulticastSingleMsg*> msgsList;
    bool bValid;

    QString getBuffer();
    QByteArray getCompletMsgArray();
};

#endif
