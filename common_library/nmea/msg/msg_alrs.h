#ifndef MSG_ALRS_H
#define MSG_ALRS_H


#include "nmea/nmea_message.h"

class MsgALRS : public NmeaMessage
{
public:
    MsgALRS();
    MsgALRS(int nSimulatorType, QString lineOne, int statusLineOne, QString lineTwo, int statusLineTwo, QString lineThree, int statusLineThree);
    // MsgALRS(int nWarnType, QString lineOne, int statusLineOne, QString lineTwo, int statusLineTwo, QString lineThree, int statusLineThree);

    int nSimulatorType; // 0: no simulator, 1: "Simulator", 2: "Alarm Test"
    QString lineOne;
    int statusLineOne; // status: 0: NO_ALARM, 1:ALR_RECTIF_UACKED, 2:  ALR_ACTIVE_RESPON_TRANS, 3: ALR_ACTIVE_ACKED, 4:ALR_ACTIVE_SILENCED, 5: ALR_ACTIVE_UACKED
    QString lineTwo;
    int statusLineTwo;
    QString lineThree;
    int statusLineThree;

    static const unsigned long ALRShash = 5001811;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgALRS *clone() {return new MsgALRS(*this);}
};

#endif
