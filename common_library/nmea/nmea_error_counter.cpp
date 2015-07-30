#include "nmea_error_counter.h"

NmeaErrorCounter::NmeaErrorCounter(QObject *parent) :
    QObject(parent)
{
}

void NmeaErrorCounter::emitSigError(int errorID)
{
    emit sigError(errorID);
}
