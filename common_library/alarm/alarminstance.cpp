#include "alarminstance.h"
//#include "utc_time.h"

AlarmInstance::AlarmInstance()
{
   // reset();
   // nRevisionCounter = 1;

    /*bAlarmEnabled   = true;
    bAlarmTrigged   = false;
    bAlarmAcked     = true;
    bExitingAlarmState = false;

    bStateChanged   = false;*/
    // stateChangedTimeStample = "";
    //nAlarmType = TYPE_NOT_ALARM;
}

// should be set by constructor
/*void AlarmInstance::setAlarmSource(AlarmSource alarmSource) {
    this->alarmSource = alarmSource;
}

// Do not use this function if state is unchanged. Timestample will be changed.
void AlarmInstance::setActive() {
    this->bAlarmActive = true;
    this->bAlarmWaitsOnACK = true;
    setTimestampleStateChanged();

    bResponsibilityTransfer = false;
    nExcalationCounter = 0; // not used yet (we always send zero)

    bSilence = false;
    nSilencedTimeCounter = 0;
}

void AlarmInstance::setAcknowledged() {
    this->bAlarmWaitsOnACK = false;

    bResponsibilityTransfer = false;
    nExcalationCounter = 0; // not used yet (we always send zero)

    bSilence = false;
    nSilencedTimeCounter = 0;

    setTimestampleStateChanged();
}

void AlarmInstance::setResponsabilityTransfered() {
    this->bAlarmWaitsOnACK = false;
    this->bResponsibilityTransfer = true;

    nExcalationCounter = 0; // not used yet (we always send zero)
    bSilence = false;
    nSilencedTimeCounter = 0;

    setTimestampleStateChanged();
}

void AlarmInstance::setRectified() { // alarm condition is over
    this->bAlarmActive = false;

    bSilence = false;
    nSilencedTimeCounter = 0;

    setTimestampleStateChanged();
}

void AlarmInstance::setTimestampleStateChanged() {
    stateChangedTimeStample = UTC_Time::getTimeStample();  // remember when state was changed (needs for ALR message)
    nRevisionCounter ++;
    if (nRevisionCounter > 99)
        nRevisionCounter = 1;
}

void AlarmInstance::setSilenced() {
    bSilence = true;
    nSilencedTimeCounter = 0;

    bResponsibilityTransfer = false;
    nExcalationCounter = 0; // not used yet (we always send zero)
}

// Alarm is ack-ed and over. Reset it to active=false, acknowledged=false
void AlarmInstance::reset() {
    bAlarmActive = false;
    bAlarmWaitsOnACK = false;
    stateChangedTimeStample = "";
    bResponsibilityTransfer = false;
    nExcalationCounter = 0; // not used yet (we always send zero)

    bSilence = false;
    nSilencedTimeCounter = 0;
}*/
