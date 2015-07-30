#include "udp_group_tag.h"
#include <QObject>

UdpGroupTag::UdpGroupTag(quint16 groupIndex, quint16 groupTotal, quint16 groupID)
{
    this->groupIndex = groupIndex;
    this->groupTotal = groupTotal;
    this->groupID    = groupID;
}

QString UdpGroupTag::getBuffer() {
    return QString("g:%1-%2-%3").arg(QString::number(groupIndex), QString::number(groupTotal), QString::number(groupID));
}
