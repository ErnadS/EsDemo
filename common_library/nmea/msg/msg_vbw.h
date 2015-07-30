//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// VBW Dual Ground/WaterSpeed
//         1   2  3  4   5  6 7
//         |   |  |  |   |  | |
// $--VBW,x.x,x.x,A,x.x,x.x,A*hh
// 1) Longitudinal water speed, "-" means astern
// 2) Transverse water speed, "-" means port
// 3) Status, A = data valid
// 4) Longitudinal ground speed, "-" means astern
// 5) Transverse ground speed, "-" means port
// 6) Status, A = data valid
// 7) Stern transverse water speed, "-" means port
// 8) Status, A = data valid
// 9) Stern transverse ground speed, "-" means port
// 10) Status, A = data valid
// 11) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_VBW_H
#define MSG_VBW_H

#include "nmea/nmea_message.h"

class MsgVBW : public NmeaMessage
{
public:
    MsgVBW();
    MsgVBW(float longitudinalWaterSpeed, float transverseWaterSpeed, QString statusWaterSpeed,
           float longitudinalGroundSpeed, float transverseGroundSpeed, QString statusGroundSpeed,
           float sternTransWaterSpeed, QString statusSternTransWaterSpeed, float sternTransGroundSpeed,
           QString statusSternTransGroundSpeed);
    

    float longitudinalWaterSpeed;              // x.x = Longitudinal water speed, "-" means astern
    float transverseWaterSpeed;                // x.x = Transverse water speed, "-" means port
    QString statusWaterSpeed;                  // A = data valid
    float longitudinalGroundSpeed;             // x.x = Longitudinal ground speed, "-" means astern
    float transverseGroundSpeed;               // x.x = Transverse ground speed, "-" means port
    QString statusGroundSpeed;                 // A = data valid
    float sternTransWaterSpeed;                // x.x = Stern transverse water speed, "-" means port
    QString statusSternTransWaterSpeed;        // A = data valid
    float sternTransGroundSpeed;               // x.x = Stern transverse ground speed, "-" means port
    QString statusSternTransGroundSpeed;       // A = data valid
    

    static const unsigned long VBWhash = 5653079;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgVBW * clone() {return new MsgVBW(*this);}
};

#endif
