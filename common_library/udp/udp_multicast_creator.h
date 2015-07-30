#ifndef UDP_MULTICAST_CREATOR_H
#define UDP_MULTICAST_CREATOR_H

#include "udp_multicast_group_msg.h"
#include "udp_multicast_single_msg.h"
#include "udp/tag/udp_source_tag.h"
#include "udp/tag/udp_destination_tag.h"
#include "udp/tag/udp_group_tag.h"

#include "nmea/nmea_message.h"

class UdpMulticastCreator
{
public:
    // Single messages
    static UdpMulticastSingleMsg createSingleMsgNoDest(NmeaMessage * nmeaMsg);
    static UdpMulticastSingleMsg createSingleMsgWithDest(NmeaMessage * nmeaMsg);

    static UdpMulticastSingleMsg createSingleMsg(NmeaMessage* nmeaMsg);
    static UdpMulticastSingleMsg createSingleMsg(NmeaMessage* nmeaMsg, UdpDestinationTag* destin);

    // Group messages
    static UdpMulticastGroupMsg createGroupMessageNoDest(QList<NmeaMessage*> nmeaList);
    static UdpMulticastGroupMsg createGroupMessageWithDest(QList<NmeaMessage*> nmeaList);


    static UdpMulticastGroupMsg createGroupMessage(QList<NmeaMessage*> nmeaList);
    static UdpMulticastGroupMsg createGroupMessage(QList<NmeaMessage*> nmeaList, UdpDestinationTag * destination);

    static QByteArray getMulticastPrefixHeader();

private:
    static void increaseMsgCounter();
    static void increaseGropIdCounter();
    static UdpMulticastSingleMsg createSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group);
    static UdpMulticastSingleMsg createSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group, UdpDestinationTag* destination);
    static QString getSourceSFI();
    static QString getPairedSFI();
};

#endif
