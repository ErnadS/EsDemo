//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// CUR    Water current layer - Multi-layer water current data ( IEC 61162-1_aed_2010.pdf, page 41.)
//        1 2  3   4   5  6  7   8   9  10 11  12
//        | |  |   |   |  |  |   |   |  |   |  |
// $--CUR,A,x,xx,x.x,x.x,a,x.x,x.x,x.x,a,  a*hh
// 1) A = Validity of data ( A = Valid, V = not valid)
// 2) x = Data set number (0 - 9)
// 3) xx = Layer number
// 4) x.x = Current depth in meters
// 5) x.x = Current direction in degrees
// 6) a = Direction reference in use (True/Reletive - T/R)
// 7) x.x = Current speed in knots
// 8) x.x = Reference layer depth in meters
// 9) x.x = heading
// 10) a = Hedaing reference in use (True/Magnetic - T/M)
// 11) a = Speed reference (B: Bottom track, W: Water track, P: Positioning system)
// 12) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_CUR_H
#define MSG_CUR_H

#include "nmea/nmea_message.h"

class MsgCUR : public NmeaMessage
{
public:
    MsgCUR();
    MsgCUR(QString validityOfData, int dataSetNumber, int layerNumber, float currentDepthInMeters,
           float CurrentDirectionIndegrees, QString directionReferenceInUse, float currentSpeedInKnots,
           float referenceLayerDepthInMeters, float heading, QString headingReference,
           QString speedReference);

    QString validityOfData;
    int dataSetNumber;
    int layerNumber;
    float currentDepthInMeters;
    float CurrentDirectionIndegrees;
    QString directionReferenceInUse;
    float currentSpeedInKnots;
    float referenceLayerDepthInMeters;
    float heading;
    QString headingReference;
    QString speedReference;

    static const unsigned long CURhash = 4412754;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgCUR * clone() {return new MsgCUR(*this);}
};

#endif
