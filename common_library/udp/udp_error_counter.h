#ifndef UDP_ERROR_COUNTER_H
#define UDP_ERROR_COUNTER_H

#include <QObject>

class UdpErrorCounter : public QObject
{
    Q_OBJECT

public:
    explicit UdpErrorCounter(QObject *parent = 0);

    void emitSigError(int errorID);

signals:
    void sigError(int errorID);
};

#endif
