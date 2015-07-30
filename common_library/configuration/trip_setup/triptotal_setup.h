#ifndef TRIPTOTAL_SETUP_H
#define TRIPTOTAL_SETUP_H

#include "triptotal_setup_s.h"

class TripTotal_Setup
{
    TripTotal_Setup_s tripTotal_Setup_s;

    bool setupReceivedFlag;

    void readSetup();
    void writeSetup();

public:
    TripTotal_Setup();

    void setTotalTrip(float total, float trip);

    float getTotal() const;
    void setTotal(float value);

    float getTrip() const;
    void setTrip(float value);

    bool getSetupReceivedFlag();


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
};

#endif // TRIPTOTAL_SETUP_H


