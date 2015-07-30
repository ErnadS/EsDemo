#include "udp_counter_tag.h"

UdpCounterTag::UdpCounterTag()
{

}

UdpCounterTag::UdpCounterTag(quint16 counter)
{
    this->counter = counter;
}


QString UdpCounterTag::getBuffer() {
    QString strCounter;
    strCounter.sprintf("%03d", counter);
    return QString("n:%1").arg(strCounter);
}
