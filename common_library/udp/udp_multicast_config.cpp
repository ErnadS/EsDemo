#include "udp_multicast_config.h"

#define DEFAULT_THIS_TALKER_ID          "SA"
#define DEFAULT_THIS_SYSTEM_ID          9999
#define DEFAULT_PAIRED_TALKER_ID        "DP"
#define DEFAULT_PAIRED_SYSTEM_ID        9999

bool UdpMulticastConfig::init()
{
    return createDefault();
}

QString UdpMulticastConfig::getThisTalker()
{
    return thisTalkerId;
}

quint16 UdpMulticastConfig::getThisSystemId()
{
    return thisSystemId;
}

bool UdpMulticastConfig::createDefault()
{
    thisTalkerId    = DEFAULT_THIS_TALKER_ID;
    thisSystemId    = DEFAULT_THIS_SYSTEM_ID;

    pairedTalkerId  = DEFAULT_PAIRED_TALKER_ID;  // Default talker ID for touch display (project 9102)
    pairedSystemId  = DEFAULT_PAIRED_SYSTEM_ID;

    return true;
}
