#ifndef UDP_MULTICAST_PARSER_H
#define UDP_MULTICAST_PARSER_H

#include <QtGlobal>
#include <QString>

#include "udp_multicast_group_msg.h"
#include "udp_multicast_single_msg.h"
#include "udp/tag/udp_source_tag.h"
#include "udp/tag/udp_destination_tag.h"
#include "udp/tag/udp_group_tag.h"

#include "nmea/nmea_message.h"

#include <QtNetwork>
#include <QUdpSocket>
#include "udp_error_counter.h"

class UdpMulticastParser : public QObject
{
    Q_OBJECT
public:
    UdpMulticastParser();
    static UdpMulticastGroupMsg* parseUdpAsciMsg(QString udpMsg);
    static UdpErrorCounter* errorCounter;

private:
    static bool parseOneMsg         (QString tagMsg, UdpMulticastSingleMsg * udpMulticastMsg);
    // UDP tags:
    static int  getGroupTag         (QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg);
    static int  getSourceTag        (QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg);
    static int  getDestinationTag   (QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg);
    static int  getMsgIndexTag      (QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg);
};

#endif
