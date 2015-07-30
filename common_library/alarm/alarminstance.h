#ifndef ALARMINSTANCE_H
#define ALARMINSTANCE_H

#include <qstring.h>
//#include "alarmcontroller.h"

enum AlarmSource {
    UNKNOWN_SOURCE          = -1,
    ALARM_LOW_SPEED_WATER   = 0,
    ALARM_HIGH_SPEED_WATER,
    ALARM_LOW_SPEED_GROUND,
    ALARM_HIGH_SPEED_GROUND,
    ALARM_SYSTEM
};


enum SystemAlarmType {
    // used only for system alarm
    SYS_NOT_ALARM = 0,
    SYS_SENSOR_LOST,
    SYS_DISPLAY_LOST,
    SYS_ALARM_TEST
};



class AlarmInstance
{
public:
    AlarmInstance();

   /* bool bAlarmActive;              // "active" means "reised" or "in alarm condition"
    bool bAlarmWaitsOnACK;          // opposite to "acked" ("false" in idle)
    bool bResponsibilityTransfer;   // used only when ALF choosed
    bool bSilence;                  // used only when ALF choosed
    int  nSilencedTimeCounter;    // used only by ALF
    int  nRevisionCounter;   // 1-99 (used by ALF, probaly ALR should also use it?)
    // Not used yet:
    int nExcalationCounter; // 0-9 (used only by ALF)
    // int nSecSinceLastExcalation = 0; // if not acked, this is increasing. If >


    AlarmSource     alarmSource;     // Low STW, High STW, ...
    SystemAlarmType systemAlarmType; // used only when alarmSource="ALARM_SYSTEM" (sensor lost, display lost or test)

    QString stateChangedTimeStample;

    void setAlarmSource(AlarmSource alarmSource);
    void setActive();
    void setAcknowledged();
    void setSilenced();
    void setResponsabilityTransfered();
    void setRectified();

    void reset(); // alarm is ack-ed and over. Reset it to active=false, acknowledged=false


private:
    void setTimestampleStateChanged();*/

};

#endif // ALARMSTATE_H
