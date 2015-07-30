#ifndef UDP_COUNTERTAG_H
#define UDP_COUNTERTAG_H

#include <QtGlobal>
#include <QString>


class UdpCounterTag
{
public:
    quint16 counter;

    UdpCounterTag();
    UdpCounterTag(quint16 counter);
    QString getBuffer();
};

#endif
