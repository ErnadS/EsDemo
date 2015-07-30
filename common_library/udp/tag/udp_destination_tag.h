#ifndef UDP_DESTINATION_TAG_H
#define UDP_DESTINATION_TAG_H

#include <QtGlobal>
#include <QString>

class UdpDestinationTag
{
public:
    QString sfi;
    UdpDestinationTag(QString sfi);
    UdpDestinationTag(QString talkerId, quint16 systemId);
    QString getBuffer();
    QString getTag();
};

#endif
