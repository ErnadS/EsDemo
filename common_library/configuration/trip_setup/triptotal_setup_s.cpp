#include "triptotal_setup_s.h"


TripTotal_Setup_s::TripTotal_Setup_s(QObject *parent) :
    QObject(parent)
{
}

float TripTotal_Setup_s::getTotalDistance() const{
    return totalDistance;
}


float TripTotal_Setup_s::getTripDistance() const{
    return tripDistance;
}

void TripTotal_Setup_s::setTotalDistance(float value) {
    totalDistance = value;
}

void TripTotal_Setup_s::setTripDistance(float value) {
    tripDistance = value;
}


