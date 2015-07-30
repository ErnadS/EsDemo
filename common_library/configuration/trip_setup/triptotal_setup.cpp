#include "triptotal_setup.h"

TripTotal_Setup::TripTotal_Setup()
{
    readSetup();
    setupReceivedFlag = false;
}

void TripTotal_Setup::readSetup()
{
    if (!SerializationController::Deserialize(tripTotal_Setup_s, "total_trip_setup", "/setup_files/"))
    {
        tripTotal_Setup_s.setTotalDistance(0.0f);
        tripTotal_Setup_s.setTripDistance(0.0f);

        writeSetup();
    }
}

void TripTotal_Setup::writeSetup()
{
    SerializationController::Serialize(tripTotal_Setup_s, "total_trip_setup", "/setup_files/");
}

void TripTotal_Setup::setTotalTrip(float total, float trip) {
    tripTotal_Setup_s.setTotalDistance(total);
    tripTotal_Setup_s.setTripDistance(trip);
    setupReceivedFlag = true;
    writeSetup();
}

float TripTotal_Setup::getTotal() const{
    return tripTotal_Setup_s.getTotalDistance();
}

void TripTotal_Setup::setTotal(float value){
    tripTotal_Setup_s.setTotalDistance(value);
    writeSetup();
}

float TripTotal_Setup::getTrip() const {
    return tripTotal_Setup_s.getTripDistance();
}

void TripTotal_Setup::setTrip(float value){
    tripTotal_Setup_s.setTripDistance(value);
    writeSetup();
}

bool TripTotal_Setup::getSetupReceivedFlag()
{
    return setupReceivedFlag;
}

bool TripTotal_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(tripTotal_Setup_s, "total_trip_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool TripTotal_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(tripTotal_Setup_s, "total_trip_setup" + fileSuffix, "/setup_files/saved_configs/");
}
