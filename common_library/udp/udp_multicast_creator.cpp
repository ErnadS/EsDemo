#include "udp_multicast_creator.h"
#include "configuration/system_setup.h"

static quint16 udpMsgCounter  = 0;  // form 0 to 999 (TODO: check specification)
static quint16 nextUdpGroupId = 1;  // form 1 to  99 (TODO: check specification)

static QByteArray udpAcsiiPrefix;

QString UdpMulticastCreator::getSourceSFI() {
#ifdef SYSTEM_JB70
        return SystemSetup::getInstance()->Jb70Setup.getLocalID();
#else
        return SystemSetup::getInstance()->CuM001Setup.getLocalID();
#endif
}

// Note: JB80 doesn't have paired ID?
QString UdpMulticastCreator::getPairedSFI() {
#ifdef SYSTEM_JB70
        return "ER0001";
#else
        return SystemSetup::getInstance()->CuM001Setup.getPairedID();
#endif
}


UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsgNoDest(NmeaMessage* nmeaMsg) {
    QString localId = getSourceSFI();

    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, new UdpSourceTag(localId), udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}

UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsgWithDest(NmeaMessage * nmeaMsg) {
    QString localId  = getSourceSFI();
    QString pairedId = getPairedSFI();


    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, new UdpSourceTag(localId),
                                          new UdpDestinationTag(pairedId), udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create a single UDP message (group not used) without destinations tag
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsg(NmeaMessage * nmeaMsg) //, UdpSourceTag * source)
{
    QString localId = getSourceSFI();

    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, new UdpSourceTag(localId), udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create a single UDP message (group not used) with destinations tag
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsg(NmeaMessage * nmeaMsg, UdpDestinationTag * destination)
{
    QString localId = getSourceSFI();

    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, new UdpSourceTag(localId), destination, udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create UDP group message without destintation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UdpMulticastGroupMsg UdpMulticastCreator::createGroupMessageNoDest(QList<NmeaMessage *> nmeaList)
{
    return createGroupMessage(nmeaList);
}

UdpMulticastGroupMsg UdpMulticastCreator::createGroupMessage(QList<NmeaMessage*> nmeaList) {
    QString localId = getSourceSFI();

    int groupIndex = 1;
    int totalMsgs = nmeaList.size();
    UdpMulticastGroupMsg udpMulticastGroupMsg;


    foreach (NmeaMessage* nmeaMessage, nmeaList)  {
        udpMulticastGroupMsg.msgsList.append(new UdpMulticastSingleMsg(nmeaMessage, new UdpGroupTag(groupIndex, totalMsgs, nextUdpGroupId), new UdpSourceTag(localId), udpMsgCounter));
        increaseMsgCounter();
        groupIndex++;
    }
    increaseGropIdCounter();

    return udpMulticastGroupMsg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create UDP group message with destintation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UdpMulticastGroupMsg UdpMulticastCreator::createGroupMessageWithDest(QList<NmeaMessage *> nmeaList)
{
    QString pairedId = getPairedSFI();

    return createGroupMessage(nmeaList, new UdpDestinationTag(pairedId));
}

UdpMulticastGroupMsg UdpMulticastCreator::createGroupMessage(QList<NmeaMessage*> nmeaList, UdpDestinationTag * destination) {
    int j = 0;

    QString localId = getSourceSFI();

    int totalMsgs = nmeaList.size();
    UdpMulticastGroupMsg udpMulticastGroupMsg;

    foreach (NmeaMessage *nmeaMessage, nmeaList)
    {
        UdpDestinationTag * destTag = new UdpDestinationTag(destination->sfi);

        udpMulticastGroupMsg.msgsList.append(new UdpMulticastSingleMsg(nmeaMessage, new UdpGroupTag(j, totalMsgs, udpMsgCounter), new UdpSourceTag(localId), destTag, udpMsgCounter));
        increaseMsgCounter();
        j++;
    }
    increaseGropIdCounter();

    return udpMulticastGroupMsg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Private functions:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group)
{
    QString localId = getSourceSFI();

    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, group, new UdpSourceTag(localId), udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}


UdpMulticastSingleMsg UdpMulticastCreator::createSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group, UdpDestinationTag * destination)
{
    QString localId = getSourceSFI();

    UdpMulticastSingleMsg udpMulticastMsg(nmeaMsg, group, new UdpSourceTag(localId), destination, udpMsgCounter);

    increaseMsgCounter();
    return udpMulticastMsg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// used in tag "n:". It's message counter (from 0 to 999). Each new UDP message has a next counter.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UdpMulticastCreator::increaseMsgCounter() {
    if (udpMsgCounter >= 999) {
        udpMsgCounter = 0;
    } else {
        udpMsgCounter++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// used in tag "g:". It's group ID counter (from 1 to 99). Each new group message should use a next group ID
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UdpMulticastCreator::increaseGropIdCounter() {
    if (nextUdpGroupId >= 99) {
        nextUdpGroupId = 1;
    } else {
        nextUdpGroupId++;
    }
}

// TODO: wrong place for this function?
QByteArray UdpMulticastCreator::getMulticastPrefixHeader() {
    if (udpAcsiiPrefix.length() == 0) {  // initialise first time
        udpAcsiiPrefix.append('U');
        udpAcsiiPrefix.append('d');
        udpAcsiiPrefix.append('P');
        udpAcsiiPrefix.append('b');
        udpAcsiiPrefix.append('C');
        udpAcsiiPrefix.append('\0');
    }
    return udpAcsiiPrefix;
}
