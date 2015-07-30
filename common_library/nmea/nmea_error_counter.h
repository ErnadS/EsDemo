#ifndef NMEA_ERROR_COUNTER_H
#define NMEA_ERROR_COUNTER_H

#include <QObject>

class NmeaErrorCounter : public QObject
{
    Q_OBJECT

public:
    explicit NmeaErrorCounter(QObject* parent = 0);

    void emitSigError(int errorID);

signals:
    void sigError(int errorID);
};

#endif
