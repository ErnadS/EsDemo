#ifndef SIMULATIONPARAMETERS_H
#define SIMULATIONPARAMETERS_H

#include <QObject>
#include "nmea/nmea_include.h"

enum SimulationSource{

    SENSOR_FIXED_SPEED,
    JB_70_FIXED_SPEED
};

class SimulationParameters : public QObject
{
    Q_OBJECT

    bool SimulationModeOn;
    bool testAlarmOutputOn;
    SimulationSource simulationSource;

    float fixedSpeedLong;
    float fixedSpeedTra;

    bool changeConfirmed;

public:
    explicit SimulationParameters(QObject *parent = 0);

    bool getSimulationModeOn() const;
    void setSimulationModeOn(bool value);

    SimulationSource getSimulationSource() const;
    void setSimulationSource(const SimulationSource &value);

    bool getChangeConfirmed() const;
    void setChangeConfirmed(bool value);

    NmeaMessage* simParamsChangeRequest();
    NmeaMessage* simParamsChangeConfirm();

    float getFixedSpeedLong() const;
    void setFixedSpeedLong(float value);

    float getFixedSpeedTra() const;
    void setFixedSpeedTra(float value);

    bool getTestAlarmOutputOn() const;
    void setTestAlarmOutputOn(bool value);

signals:
    void sigSimulationParametersChanged();

public slots:

    void slotSimulationCommand(MsgICM* msg);
    void slotConfirmeChange(bool reply);

};

#endif // SIMULATIONPARAMETERS_H
