//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// VTG Track Made Good and Ground Speed
//         1  2  3  4  5  6  7  8 9
//         |  |  |  |  |  |  |  | |
// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K*hh
// 1) Track Degrees
// 2) T = True
// 3) Track Degrees
// 4) M = Magnetic
// 5) Speed Knots
// 6) N = Knots
// 7) Speed KilometersPer Hour
// 8) K = Kilometres Per Hour
// 9) A = Mode indicator (see IEC 61162-1 4ed, page 98)
// 10) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_VTG_H
#define MSG_VTG_H

#include "nmea/nmea_message.h"

class MsgVTG : public NmeaMessage
{
public:
    MsgVTG();
    MsgVTG(float trackDegresTrue, QString trueDegrees, float trackDegresMagnetic, QString magneticDegrees,
           float speedKnots, QString knots, float speedKilometers, QString kilometers, QString modeIndicator);

    float trackDegresTrue;                 // x.x = Track Degrees
    QString trueDegrees;                   // T = True
    float trackDegresMagnetic;             // x.x = Magnetic Degrees
    QString magneticDegrees;               // M = Magnetic
    float speedKnots;                      // x.x = Speed Knots
    QString knots;                         // N = Knots
    float speedKilometers;                 // x.x = Speed KilometersPer Hour
    QString kilometers;                    // K = Kilometres Per Hour
    QString modeIndicator;                 // A = Mode indicator (see IEC 61162-1 4ed, page 98)


    static const unsigned long VTGhash = 5657671;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgVTG * clone() {return new MsgVTG(*this);}
};

#endif
