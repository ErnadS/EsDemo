#ifndef UDP_SOURCE_TAG_H
#define UDP_SOURCE_TAG_H

#include <QtGlobal>
#include <QString>

class UdpSourceTag
{
public:
    QString sfi;

    UdpSourceTag(QString sfi);
    UdpSourceTag(QString talkerId, quint16 systemId);
    QString getBuffer();
    QString getTag();
};

#endif
