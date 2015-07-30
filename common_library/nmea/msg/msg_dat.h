//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// DAT    (4800 baud)
//         1   2   3   4   5   6     7     8     9     10  11  12  13  14    15   16
//         |   |   |   |   |   |     |     |     |     |   |   |   |   |     |    |
// $PSKDAT,x,+xx.x,x,+xx.x,x,+xx.x,xxx.x,xxx.x,xxx.x,+xx.x,x,+xx.x,x,xxx.x,xxx.x*hh  
// 1) SYSTEM ID (2=DL2 card 1. 3=DL2 Slave card2)
// 2) Forward Water speed 1st axis +-xx.x
// 3) Forward Water speed 1st axis signal quality (1-8) 
// 4) AFT Water Speed 1st axis +- 51.2
// 5) AFT Water Speed 1st axis signal quality (1-8)
// 6) Temperature (C)
// 7) Tilt X deg
// 8) Tilt Y deg
// 9) Tilt Z deg
// 10) Forward Water Speed 2nd axis +-51.2
// 11) Forward Water Speed 2nd axis signal quality (1-8)
// 12) AFT Water Speed 2nd axis +- 51.2
// 13) AFT Water Speed 2nd axis signal quality (1-8)
// 14) Depth FWD (000.0-200.0)
// 15) Depth AFT (000.0-200.0)
// 16) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_DAT_H
#define MSG_DAT_H

#include "nmea/nmea_message.h"

class MsgDAT : public NmeaMessage
{
public:
    MsgDAT();
    MsgDAT(int systemID, float fwdSpeedWater, int fwdSigQualityWater, float aftSpeedWater, int aftSigQualityWater,
           float fTemperature, int tiltX, int tiltY, int tiltZ, float fwdSpeedGround, int fwdSigQualityGround,
           float aftSpeedGround, int aftSigQualityGround, float depthFwd, float depthAft);

    int systemID;                      
    float fwdSpeedWater;                  // +-xx.x = Forward Water speed 1st axis
    int fwdSigQualityWater;               // x = Forward Water speed 1st axis signal quality (1-8)
    float aftSpeedWater;                  // +-xx.x = AFT Water speed 1st axis
    int aftSigQualityWater;               // x = AFT Water speed 1st axis signal quality (1-8)
    float fTemperature;                    // +-xx.x = Temperature
    int tiltX;                             // xxx = Tilt X deg
    int tiltY;                             // xxx = Tilt Y deg
    int tiltZ;                             // xxx = Tilt Z deg

    float fwdSpeedGround;                  // +-xx.x = Forward Water speed 2nd axis
    int fwdSigQualityGround;               // x = Forward Water speed 2nd axis signal quality (1-8)
    float aftSpeedGround;                  // +-xx.x = AFT Water speed 2nd axis
    int aftSigQualityGround;               // x = AFT Water speed 2nd axis signal quality (1-8)
    float depthFwd;                        // xxx.x = Depth FWD (000.0-200.0)
    float depthAft;                        // xxx.x = Depth AFT (000.0-200.0)

    static const unsigned long DAThash = 4473172;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgDAT * clone() {return new MsgDAT(*this);}
};

#endif
