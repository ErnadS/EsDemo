#include "udp_error_counter.h"

UdpErrorCounter::UdpErrorCounter(QObject *parent) :
    QObject(parent)
{
}

void UdpErrorCounter::emitSigError(int errorID)
{
    emit sigError(errorID);
}
