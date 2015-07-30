#include "udp_source_tag.h"

UdpSourceTag::UdpSourceTag(QString sfi)
{
    this->sfi = sfi;
}

UdpSourceTag::UdpSourceTag(QString talkerId, quint16 systemId)
{
    QString strId;
    strId.sprintf("%04d", systemId);

    this->sfi = QString("%1%2").arg(talkerId, strId);
}

QString UdpSourceTag::getBuffer() {
    return QString("s:%1").arg(sfi);
}

QString UdpSourceTag::getTag()
{
    return sfi;
}
