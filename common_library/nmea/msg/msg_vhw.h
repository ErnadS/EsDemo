//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// VHW Water Speed and Heading
//         1  2  3  4  5  6  7  8 9
//         |  |  |  |  |  |  |  | |
// $--VHW,x.x,T,x.x,M,x.x,N,x.x,K*hh
// 1) DegressTrue
// 2) T = True
// 3) Degrees Magnetic
// 4) M = Magnetic
// 5) Knots (speed of vessel relative to the water)
// 6) N = Knots
// 7) Kilometers(speed of vessel relative to the water)
// 8) K = Kilometres
// 9) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_VHW_H
#define MSG_VHW_H

#include "nmea/nmea_message.h"

class MsgVHW : public NmeaMessage
{
public:
    MsgVHW();
    MsgVHW(float degressTrue, QString typeDegressOne, float degressMagnetic, QString typeDegressTwo,float speedKnots,
           QString unitSpeedOne, float speedKilometers, QString unitSpeedTwo);


    float degressTrue;                 // x.x = Degress True
    QString typeDegressOne;            // T = True
    float degressMagnetic;             // x.x = Degress Magnetic
    QString typeDegressTwo;            // M = Magnetic
    float speedKnots;                  // x.x = Knots (speed of vessel relative to the water)
    QString unitSpeedOne;              // N = Knots
    float speedKilometers;             // x.x = Kilometers (speed of vessel relative to the water)
    QString unitSpeedTwo;              // K = Kilometres


    static const unsigned long VHWhash = 5654615;

    bool setParams(QStringList m_message_parameters);
    virtual QString getMsgBuffer();

    MsgVHW * clone() {return new MsgVHW(*this);}
};

#endif
