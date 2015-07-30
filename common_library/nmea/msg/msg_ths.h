//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// THS True heading and status
//         1  2  3
//         |  |  |
// $--THS,x.x,a*hh
// 1) Heading Degrees, true
// 2) Mode indicator (A-Autonomous, E-Estimated (dead reckoning), M-Manual input, S-Simulator mode, V-Data not valid)
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_THS_H
#define MSG_THS_H

#include "nmea/nmea_message.h"

class MsgTHS : public NmeaMessage
{
public:
    MsgTHS();
    MsgTHS(float headingDegrees, QString modeIndicator);


    float headingDegrees;                  // x.x = Heading Degrees, true
    QString modeIndicator;                    // T = True


    static const unsigned long THShash = 5523539;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgTHS * clone() {return new MsgTHS(*this);}
};

#endif
