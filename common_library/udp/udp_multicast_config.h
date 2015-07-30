#ifndef UDP_MULTICAST_CONFIG_H
#define UDP_MULTICAST_CONFIG_H

#include <QObject>

class UdpMulticastConfig: public QObject
{
    Q_OBJECT

public:
    bool init();
    bool redisRead();
    bool redisSave();

    QString getThisTalker();
    quint16 getThisSystemId();

private:

    QString thisTalkerId;
    quint16 thisSystemId;

    QString pairedTalkerId;
    quint16 pairedSystemId;

    bool createDefault();
};

#endif
