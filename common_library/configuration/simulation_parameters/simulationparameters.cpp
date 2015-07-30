#include "simulationparameters.h"
#include "utility/unitconverter.h"


bool SimulationParameters::getSimulationModeOn() const
{
    return SimulationModeOn;
}

void SimulationParameters::setSimulationModeOn(bool value)
{
    SimulationModeOn = value;
}

SimulationSource SimulationParameters::getSimulationSource() const
{
    return simulationSource;
}

void SimulationParameters::setSimulationSource(const SimulationSource &value)
{
    simulationSource = value;
}

bool SimulationParameters::getChangeConfirmed() const
{
    return changeConfirmed;
}

void SimulationParameters::setChangeConfirmed(bool value)
{
    changeConfirmed = value;
}

NmeaMessage *SimulationParameters::simParamsChangeRequest()
{
    changeConfirmed = false;
    return new MsgICM(SimulatinCommand, QList<int>()
                      << SimulationModeOn
                      << testAlarmOutputOn
                      << (int)simulationSource
                      << UnitConverter::floatToInt(fixedSpeedLong)
                      << UnitConverter::floatToInt(fixedSpeedTra)
                      << (int)REQUEST);
}

NmeaMessage *SimulationParameters::simParamsChangeConfirm()
{
    changeConfirmed = true;
    return new MsgICM(SimulatinCommand, QList<int>()
                      << SimulationModeOn
                      << testAlarmOutputOn
                      << (int)simulationSource
                      << UnitConverter::floatToInt(fixedSpeedLong)
                      << UnitConverter::floatToInt(fixedSpeedTra)
                      << (int)CONFIRMED);
}

float SimulationParameters::getFixedSpeedLong() const
{
    return fixedSpeedLong;
}

void SimulationParameters::setFixedSpeedLong(float value)
{
    fixedSpeedLong = value;
}

float SimulationParameters::getFixedSpeedTra() const
{
    return fixedSpeedTra;
}

void SimulationParameters::setFixedSpeedTra(float value)
{
    fixedSpeedTra = value;
}

void SimulationParameters::slotSimulationCommand(MsgICM *msg)
{
    SimulationModeOn = msg->msgParameters[0];
    testAlarmOutputOn = msg->msgParameters[1];
    simulationSource = (SimulationSource)msg->msgParameters[2];
    fixedSpeedLong = UnitConverter::intToFloat(msg->msgParameters[3]);
    fixedSpeedTra = UnitConverter::intToFloat(msg->msgParameters[4]);

    if(msg->msgParameters[5] == (int)CONFIRMED)
        changeConfirmed = true;
    else
        changeConfirmed = false;

    emit sigSimulationParametersChanged();
}

void SimulationParameters::slotConfirmeChange(bool reply)
{
    if(reply)
        changeConfirmed = true;
    else
    {
        SimulationModeOn = false;
        emit sigSimulationParametersChanged();
    }
}

bool SimulationParameters::getTestAlarmOutputOn() const
{
    return testAlarmOutputOn;
}

void SimulationParameters::setTestAlarmOutputOn(bool value)
{
    testAlarmOutputOn = value;
}

SimulationParameters::SimulationParameters(QObject *parent) :
    QObject(parent)
{
    SimulationModeOn = false;
    testAlarmOutputOn = false;
    simulationSource = SENSOR_FIXED_SPEED;

    fixedSpeedLong = 1.0f;
    fixedSpeedTra = 1.0f;

    changeConfirmed = true;
}
