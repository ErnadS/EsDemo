#include "udp_multicast_group_msg.h"
#include "udp_multicast_creator.h"

// One UDP datagram can consist of one or mulitpele messages. If multiple, thay must be with group tag?
// We are allowing without group tag (more than one message in one datagram and messages are not with group tag).
UdpMulticastGroupMsg::UdpMulticastGroupMsg()
{
    bValid = true;
}

UdpMulticastGroupMsg::~UdpMulticastGroupMsg()
{

     foreach (UdpMulticastSingleMsg* single, msgsList) {
        if (single != NULL) {
            delete single;
            single = NULL;
        }
    }
/*
    if (udpSourceTag != NULL)       // Should not be a NULL but in case that something was wrong in this message
        delete(udpSourceTag);
    if (udpDestinationTag != NULL)  // Is not mandatory (can be a NULL). Check is it used before deleting.
        delete udpDestinationTag;
    if (udpGroupTag != NULL)        // Is not mandatory (can be a NULL). Check is it used before deleting.
        delete udpGroupTag;*/
}


// TODO: desctructor (free all from the list?)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Created buffer is in format: "/g:0-1-88,s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n/g:0-2-88,s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function can be used when creating group of messages (without "UdPbC" in the start). User will probably
// create multiple messages using this function and than add "UdPbC" in the start before sending.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString UdpMulticastGroupMsg::getBuffer() {
    QString msg;
    // TODO: check max UPD message length (around 1450 bytes).
    QList<UdpMulticastSingleMsg*>::iterator pUdpMulticastMsg;

    //int totalMsgs = msgsList.size();

    for (pUdpMulticastMsg = msgsList.begin(); pUdpMulticastMsg != msgsList.end(); ++pUdpMulticastMsg)
    {
        msg += (*pUdpMulticastMsg)->getBuffer();
    }

    return msg;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Created buffer is in format: "UdPbC<null>/g:0-1-88,s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n/g:0-2-88,s:0301,d:9003,n:002*3F/$VDVMM,0.2,3*45\r\n"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This funciton is used when sending group NMEA message. "UdPbC" will be added in the start of the message
// and this buffer can be sent directly (format specifized by 61162-450 standard).
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QByteArray UdpMulticastGroupMsg::getCompletMsgArray() {
    QString msg = getBuffer();
    QByteArray completMsg = UdpMulticastCreator::getMulticastPrefixHeader(); // Add "UdPbC\0" in the start
    completMsg.append(msg.toLatin1());
    return completMsg;
}
