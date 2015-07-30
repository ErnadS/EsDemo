#include "udp_destination_tag.h"

UdpDestinationTag::UdpDestinationTag(QString sfi)
{
    this->sfi = sfi;
}

UdpDestinationTag::UdpDestinationTag(QString talkerId, quint16 systemId)
{
    QString strId;
    strId.sprintf("%04d", systemId);

    this->sfi = QString("%1%2").arg(talkerId, strId);
}


QString UdpDestinationTag::getBuffer() {
    return QString("d:%1").arg(sfi);
}

QString UdpDestinationTag::getTag()
{
    return sfi;
}
