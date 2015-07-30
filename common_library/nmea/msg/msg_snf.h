//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// SNF (4800 baud)
//          1    2    3  4   5     6   7  8   9  10
//          |    |    |  |   |     |   |  |   |  |
// $PSKPSNF,x,xxxxxx,Ax,xxx,xxxx,xxxx,xx,xxx,xx*nn
// 1) ID : 1 for DL1
// 2) Serial number 6 digits 130001
// 3) HW revision (Letter and number A1 )
// 4) Firmware revision 1.02 = 102
// 5) Scaling factor (XXXX /100) for beam 1 configuration and calibration scaling.
// 6) Scaling factor (XXXX /100) for beam 2 configuration and calibration scaling.
// 7) Offset for temperature sensor
// 8) Scaling factor for temperature speed correction
// 9) Frequency number. ?5=270, ?10=555,?15=715
// 10) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_SNF_H
#define MSG_SNF_H

#include "nmea/nmea_message.h"

class MsgSNF : public NmeaMessage
{
public:
    MsgSNF();
    MsgSNF(int systemID, int serialNumber, QString hardwareRev, float firmwereRev, float scalingForBeam1,
           float scalingForBeam2, float offsetTempSens, float scalingTempSpeed, int frequencyNr);

    int systemID;
    int serialNumber;                      // xxxxxx = Serial number 6 digits 130001
    QString hardwareRev;                   // Ax = HW revision (Letter and number A1 )
    float firmwereRev;                     // xxx = Firmware revision 1.02 = 102
    float scalingForBeam1;                 // xxxx = Scaling factor (XXXX /100) for beam 1 configuration and calibration scaling.
    float scalingForBeam2;                 // xxxx = Scaling factor (XXXX /100) for beam 2 configuration and calibration scaling.
    float offsetTempSens;                  // xx = Offset for temperature sensor
    float scalingTempSpeed;                // xxx = Scaling factor for temperature speed correction
    int frequencyNr;                       // xx = Frequency number. ?5=270, ?10=555,?15=715


    static const unsigned long SNFhash = 5459526;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSNF * clone() {return new MsgSNF(*this);}
};

#endif
