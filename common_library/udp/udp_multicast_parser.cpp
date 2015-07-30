#include "udp_multicast_parser.h"
#include "utility/crc8.h"
#include "nmea/nmea_message.h"
#include "nmea/nmea_parser.h"

#include <qdebug.h>

#define MAX_UDP_LENGTH  1454  // 1500 - 14 (Ethernet header (MAC)) - 32 bytes (UDP header)

UdpErrorCounter* UdpMulticastParser::errorCounter = new UdpErrorCounter();

UdpMulticastParser::UdpMulticastParser()
{
}

// Note !!!: argument is buffer without leading "UdPbc<null>"
UdpMulticastGroupMsg* UdpMulticastParser::parseUdpAsciMsg(QString udpMsg) {
     int nIndex;
     QString nextNmea;
     UdpMulticastGroupMsg* udpMulticastGroupMsg = new UdpMulticastGroupMsg();
     UdpMulticastSingleMsg * udpMulticastMsg;

     if(udpMsg.length() > MAX_UDP_LENGTH)
     {
         udpMulticastGroupMsg->bValid = false;
         errorCounter->emitSigError(ERR_TYPE_UDP_OVERFL_REASEM);
     }

     nIndex = udpMsg.indexOf("\r\n");
     while(nIndex > 0) {
         // Take one message from the group (if group used) and parse it
         nextNmea = udpMsg.left(nIndex + 2);
         //------------------------------qDebug() << "NMEA: " << nextNmea;

         udpMulticastMsg = new UdpMulticastSingleMsg();  // TODO: check does we need delete and desctructor

         // parse one message
         if (!parseOneMsg(nextNmea, udpMulticastMsg)) {
             qDebug() << "!!! ERROR NMEA  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx: " << nextNmea;
             udpMulticastGroupMsg->bValid = false;
         } else {
           //  qDebug() << "NMEA: " << nextNmea;
         }

         udpMsg  = udpMsg.mid(nIndex + 2);
         nIndex  = udpMsg.indexOf("\r\n");

         udpMulticastGroupMsg->msgsList.append(udpMulticastMsg);
     }

     if (udpMsg.length() > 0) {
         udpMulticastGroupMsg->bValid = false;
         qDebug() << " WARNING: Udp message: unexpected chars after new line: " << udpMsg;
         return udpMulticastGroupMsg; // TODO
     }
     return udpMulticastGroupMsg;
}

bool UdpMulticastParser::parseOneMsg(QString msg, UdpMulticastSingleMsg * udpMulticastMsg) {
    QString msgTag;
    QString msgNmeaBody;

    int nIndex;

    if (msg[0] != '\\')  {// missing tag-start (must starts with e.g. "\s:VD.....\")
        udpMulticastMsg->msgStatus = UDP_ERR_TAG_FORMAT;
        errorCounter->emitSigError(ERR_TYPE_TAG_FRAMING);
        qDebug() << "Wrong group tag format in UDP msg !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1 ";
        qDebug() << msg;
        return false;
    }

    msg = msg.mid(1);  // remove tag start ('\')
    nIndex = msg.indexOf("\\");
    if (nIndex < 0)  {// mising tag end
        udpMulticastMsg->msgStatus = UDP_ERR_TAG_FORMAT;
        errorCounter->emitSigError(ERR_TYPE_TAG_FRAMING);
        qDebug() << "UDP_ERR_TAG_FORMAT";
        return false;
    }

    msgTag = msg.left(nIndex);  // msgTag is tag without '\' on the start and end
    msgNmeaBody = msg.mid(nIndex + 1); // rest is body (NMEA msg)

    int crcResult = CRC8::validateCrc(msgTag);
    if (crcResult != CRC_8_OK) { // CRC is mandatory in tag header // && crcResult != NO_CRC)
        udpMulticastMsg->msgStatus = UDP_ERR_TAG_CRC;
        errorCounter->emitSigError(ERR_TYPE_TAG_CRC);
        qDebug() << "UDP_ERR_TAG_CRC";
        return false;
    }


    if (getGroupTag(msgTag, udpMulticastMsg) < 0) { // get group tag (if any). Not mandatory
        errorCounter->emitSigError(ERR_TYPE_TAG_SINTAX);
        qDebug() << "Wrong group tag format in UDP msg: " << msgTag;
        return false;
    }

    if (getSourceTag(msgTag, udpMulticastMsg) < 0) {   // Source tag is mandatory (?)
        errorCounter->emitSigError(ERR_TYPE_TAG_SINTAX);
        qDebug() << "Wrong format or missing source tag in UDP msg: " << msgTag;
        return false;
    }



    if (getMsgIndexTag(msgTag, udpMulticastMsg) < 0) {   // Msg index tag is mandatory
        errorCounter->emitSigError(ERR_TYPE_TAG_SINTAX);
        qDebug() << "Wrong format or missing msg index tag in UDP msg: " << msgTag;
        return false;
    }

    if (getDestinationTag(msgTag, udpMulticastMsg) < 0) {  // Not mandatory. If missing, msg is to all destinations
        errorCounter->emitSigError(ERR_TYPE_TAG_SINTAX);
        qDebug() << "Wrong destination tag format in UDP msg: " << msgTag;
        return false;
    }

    udpMulticastMsg->nmeaMessage = NmeaParser::parse(msgNmeaBody.toLatin1().data());

    if (udpMulticastMsg->nmeaMessage->m_error_id != NmeaMessageErrorType::NO_NMEA_ERROR)
    {
        qDebug() << "!!! ERROR NMEA  : " << (int)udpMulticastMsg->nmeaMessage->m_error_id;
        return false;
    }

    return true;
}

// TODO: define return values as Enum ...

///////////////////////////////////////////////////////////////////////////////////////////////
// Group tag
///////////////////////////////////////////////////////////////////////////////////////////////
// e.g.: "g:2-3-44" (msg index = 2, total 3, group ID = 44)
///////////////////////////////////////////////////////////////////////////////////////////////
/// \brief UdpMulticastParser::getSourceTag
/// \param tagMsg
/// \param udpGroupTag
/// \return
int UdpMulticastParser::getGroupTag(QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg) { //) {
    int nIndex;
    quint16 ind, tot, groupId;

    nIndex = tagMsg.indexOf("g:");
    if (nIndex < 0) {
        udpMulticastMsg->udpGroupTag = NULL;
        return 1;  // Not a group msg but it's not a mandatory
    }

    QString rest = tagMsg.mid(nIndex + 2);
    nIndex = rest.indexOf(",");
    if (nIndex <= 0) {
        nIndex = rest.indexOf("*"); // the last tag is finishing with CRC
    }
    if (nIndex <= 0) {
        udpMulticastMsg->msgStatus = UDP_ERR_GROUP_FORMAT;
        return -2; // missing end of tag
    }

    // TODO: try/catch?
    // TODO: check is numbers valid
    rest = rest.left(nIndex);
    nIndex = rest.indexOf("-");
    //udpGroupTag->groupIndex
            ind = rest.left(nIndex).toUInt();

    rest = rest.mid(nIndex + 1); // remove group index
    nIndex = rest.indexOf("-");
    //udpGroupTag->groupTotal
    tot = rest.left(nIndex).toUInt();

    rest = rest.mid(nIndex + 1); // remove group total

    // udpGroupTag->groupID =
    groupId = rest.toUInt();

    udpMulticastMsg->udpGroupTag = new UdpGroupTag(ind, tot, groupId);
    return 0; // OK
}

int UdpMulticastParser::getSourceTag(QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg) {
    udpMulticastMsg->udpSourceTag = NULL;
    int nIndex = tagMsg.indexOf("s:");
    if (nIndex < 0) {
        udpMulticastMsg->msgStatus = UDP_MISS_SOURCE;

        return -1;  // Not found
    }

    QString rest = tagMsg.mid(nIndex + 2);
    nIndex = rest.indexOf(",");
    if (nIndex <= 0) {
        nIndex = rest.indexOf("*"); // the last tag is finishing with CRC
    }
    if (nIndex <= 0) {
        udpMulticastMsg->msgStatus = UDP_ERR_SRC_FORMAT;
        return -2; // missing end of tag
    }

    if (nIndex != 6) {
        udpMulticastMsg->msgStatus = UDP_ERR_SRC_FORMAT;
        return -2; // Error, we are expecting e.g. VD0192 (6 chars)
    }

    udpMulticastMsg->udpSourceTag = new UdpSourceTag(rest.left(6));//mid(0, 2), (rest.mid(2, 4)).toUInt());

    return 0; // OK
}

int UdpMulticastParser::getDestinationTag(QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg) {
    udpMulticastMsg->udpDestinationTag = NULL;
    int nIndex = tagMsg.indexOf("d:");
    if (nIndex < 0) {
        return 1;  // Not found but not mandatory
    }

    QString rest = tagMsg.mid(nIndex + 2);
    nIndex = rest.indexOf(",");
    if (nIndex <= 0) {
        nIndex = rest.indexOf("*"); // the last tag is finishing with CRC
    }
    if (nIndex <= 0) {
        udpMulticastMsg->msgStatus = UDP_ERR_DEST_FORMAT;
        return -2; // missing end of tag
    }

    if (nIndex != 6) {
        udpMulticastMsg->msgStatus = UDP_ERR_DEST_FORMAT;
        return -2; // Error, we are expecting e.g. VD0192 (6 chars)
    }

    udpMulticastMsg->udpDestinationTag = new UdpDestinationTag(rest.left(6));//rest.mid(0, 2), (rest.mid(2, 4)).toUInt());
    return 0; // OK
}

int UdpMulticastParser::getMsgIndexTag(QString tagMsg, UdpMulticastSingleMsg *udpMulticastMsg) {
    quint16 * nMsgIndex = &udpMulticastMsg->udpCounterTag.counter;

    int nIndex = tagMsg.indexOf("n:");
    if (nIndex < 0) {
        udpMulticastMsg->msgStatus = UDP_ERR_MISS_COUNTER;
        return -1;  // Not found
    }

    QString rest = tagMsg.mid(nIndex + 2);  // remove all before "n:"
    // find end of tag (',' or '*')
    nIndex = rest.indexOf(",");
    if (nIndex <= 0) {
        nIndex = rest.indexOf("*"); // the last tag is finishing with CRC
    }
    if (nIndex <= 0) {
        udpMulticastMsg->msgStatus = UDP_ERR_COUNT_FORMAT;
        return -2; // missing end of tag
    }

    if (nIndex != 3) {
        udpMulticastMsg->msgStatus = UDP_ERR_COUNT_FORMAT;
        return -3; // Error, we are only accepting format "001" (3 digits). Should we accept with not leading zero?
    }

    *nMsgIndex = rest.left(nIndex).toUInt();
    if (*nMsgIndex > 999) { // should be from 0 to 999
        udpMulticastMsg->msgStatus = UDP_ERR_COUNT_FORMAT;
        return -4;
    }
    return 0; // OK
}

