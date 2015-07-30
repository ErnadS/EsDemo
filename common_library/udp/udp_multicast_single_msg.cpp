#include "udp_multicast_creator.h"
#include "udp_multicast_single_msg.h"
#include "udp_multicast_parser.h"
#include "utility/crc8.h"

UdpMulticastSingleMsg::UdpMulticastSingleMsg()
{
    udpDestinationTag = NULL;
    udpGroupTag = NULL;
    this->msgStatus = UDP_MSG_OK;
}

UdpMulticastSingleMsg::~UdpMulticastSingleMsg()
{
    if (udpSourceTag != NULL) {      // Should not be a NULL but in case that something was wrong in this message
        delete(udpSourceTag);
        udpSourceTag = NULL;
    }
    if (udpDestinationTag != NULL) { // Is not mandatory (can be a NULL). Check is it used before deleting.
        delete udpDestinationTag;
        udpDestinationTag = NULL;
    }
    if (udpGroupTag != NULL) {       // Is not mandatory (can be a NULL). Check is it used before deleting.
        delete udpGroupTag;
        udpGroupTag = NULL;
    }
}

UdpMulticastSingleMsg::UdpMulticastSingleMsg(NmeaMessage* nmeaMsg, UdpSourceTag* source, quint16 counter) {
    this->nmeaMessage = nmeaMsg;
    this->udpSourceTag = source;
    this->udpDestinationTag  = NULL;
    this->udpGroupTag = NULL;
    udpCounterTag.counter = counter;
}

UdpMulticastSingleMsg::UdpMulticastSingleMsg(NmeaMessage* nmeaMsg, UdpSourceTag* source, UdpDestinationTag* destination, quint16 counter)
                /*:nmeaMessage(nmeaMsg), udpSourceTag(source), udpDestinationTag(destination) */{
    this->nmeaMessage = nmeaMsg;
    this->udpSourceTag = source;
    this->udpDestinationTag = destination;
    this->udpGroupTag = NULL;

    udpCounterTag.counter = counter;
}

UdpMulticastSingleMsg::UdpMulticastSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group, UdpSourceTag* source, quint16 counter)
{
    this->nmeaMessage = nmeaMsg;
    this->udpSourceTag = source;
    this->udpGroupTag = group;
    this->udpDestinationTag  = NULL;

    udpCounterTag.counter = counter;
}


UdpMulticastSingleMsg::UdpMulticastSingleMsg(NmeaMessage* nmeaMsg, UdpGroupTag* group, UdpSourceTag* source, UdpDestinationTag* destination, quint16 counter)
{
    this->nmeaMessage = nmeaMsg;
    this->udpSourceTag = source;
    this->udpDestinationTag = destination;
    this->udpGroupTag = group;

    udpCounterTag.counter = counter;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Created buffer is in format: "/s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function can be used for creating msg buffer without "UdPbC" in the start. User will probably
// create multiple messages using this function and than add "UdPbC" in the start before sending.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString UdpMulticastSingleMsg::getBuffer() {
    QString tags;

    if (udpDestinationTag  != NULL)
        tags = QString("%1,%2,%3").arg(udpSourceTag->getBuffer(), udpDestinationTag->getBuffer(), udpCounterTag.getBuffer());
    else {
        QString src = udpSourceTag->getBuffer();
        QString counter = udpCounterTag.getBuffer();
        tags = QString("%1,%2").arg(udpSourceTag->getBuffer(), udpCounterTag.getBuffer());
    }

    if (udpGroupTag != NULL) {
        tags = QString("%1,%2").arg(udpGroupTag->getBuffer(), tags);
    }

    QString crc = CRC8::calculateChecksum(tags);
    tags = QString("\\%1*%2\\%3").arg(tags, crc, nmeaMessage->getMsgBuffer());
    return tags;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Created buffer is in format: "UdPbC<null>/s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This funciton is used when sending only one NMEA message. "UdPbC" will be added in the start of the message
// and this buffer can be sent directly (format specifized by 61162-450 standard).
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QByteArray UdpMulticastSingleMsg::getCompletMsgArray() {
    QString tagsAndNmea = getBuffer();
    QByteArray completMsg = UdpMulticastCreator::getMulticastPrefixHeader(); // Add "UdPbC\0" in the start
    completMsg.append(tagsAndNmea.toLatin1());
    return completMsg;
}



