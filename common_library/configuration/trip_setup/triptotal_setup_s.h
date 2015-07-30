#ifndef TRIPTOTAL_SETUP_S_H
#define TRIPTOTAL_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class TripTotal_Setup_s: public QObject
{
    Q_OBJECT

    float totalDistance;
    float tripDistance;

    Q_PROPERTY(float totalDistance READ getTotalDistance WRITE setTotalDistance)
    Q_PROPERTY(float tripDistance READ getTripDistance WRITE setTripDistance)

public:
    explicit TripTotal_Setup_s(QObject *parent = 0);

    float getTotalDistance() const;
    void setTotalDistance(float value);

    float getTripDistance() const;
    void setTripDistance(float value);
};

#endif // TRIPTOTAL_SETUP_S_H

