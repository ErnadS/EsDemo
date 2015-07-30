#ifndef UDP_MULTICAST_MSG_H
#define UDP_MULTICAST_MSG_H

#include <QtGlobal>
#include <QString>

#include "tag/udp_source_tag.h"
#include "tag/udp_destination_tag.h"
#include "tag/udp_group_tag.h"
#include "tag/udp_counter_tag.h"

#include "nmea/nmea_message.h"

enum UdpMsgStatus{
    UDP_MSG_OK                  = 0,
    UDP_MISS_SOURCE             = 1,        // tag source is mandatory

    UDP_ERR_SRC_FORMAT          = 2,
    UDP_ERR_DEST_FORMAT         = 3,
    UDP_ERR_GROUP_FORMAT        = 4,

    UDP_ERR_MISS_COUNTER        = 5,
    UDP_ERR_COUNT_FORMAT        = 6,        // tag counter (msg index) is mandatory
    UDP_ERR_TAG_FORMAT          = 7,
    UDP_ERR_TAG_CRC             = 10
};

class UdpMulticastSingleMsg
{
public:
    UdpSourceTag  *      udpSourceTag;
    UdpDestinationTag *  udpDestinationTag;
    UdpCounterTag        udpCounterTag; // from 0 - 999
    UdpGroupTag   *      udpGroupTag;
    NmeaMessage *         nmeaMessage;

    UdpMsgStatus         msgStatus;

    UdpMulticastSingleMsg();
    ~UdpMulticastSingleMsg();
    // No group, no destination
    UdpMulticastSingleMsg(NmeaMessage * nmeaMsg, UdpSourceTag * source, quint16 counter);
    // no gruop
    UdpMulticastSingleMsg(NmeaMessage * nmeaMsg, UdpSourceTag * source, UdpDestinationTag * destination, quint16 counter);

    // with group, no destination
    UdpMulticastSingleMsg(NmeaMessage * nmeaMsg, UdpGroupTag* group, UdpSourceTag* source, quint16 counter);
    // with group and destination
    UdpMulticastSingleMsg(NmeaMessage * nmeaMsg, UdpGroupTag* group, UdpSourceTag* source, UdpDestinationTag* destination, quint16 counter);
    QString getBuffer();
    QByteArray getCompletMsgArray();
};

#endif
