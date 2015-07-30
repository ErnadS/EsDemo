#ifndef UDP_GROUPTAG_H
#define UDP_GROUPTAG_H

#include <QtGlobal>
#include <QtGlobal>

class UdpGroupTag
{
public:
    quint16 groupIndex;     // from 0 - 9?
    quint16 groupTotal;
    quint16 groupID;        // from 0 - 99?

    UdpGroupTag(quint16 groupIndex, quint16 groupTotal, quint16 groupID);
    QString getBuffer();
};

#endif
