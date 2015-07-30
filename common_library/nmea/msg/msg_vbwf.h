//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// VBWF   handle uncalibrated speed
//             1 2 3  4-10    11
//             | | |    |      |
// $PSKPVBWF,xx.x,,A,,,V,,V,,V*nn
// 1) Forward averaged Speed in 1/100 kn (+-50kn)
// 2) Empty
// 3) A is status of data
// 4 - 10) Fixed, unused
// 11) Checksum
//////////////////////////////////////////////////////////////

#include "nmea/nmea_message.h"

#ifndef MSG_VBWF_H
#define MSG_VBWF_H

class MsgVBWF : public NmeaMessage
{
public:
    MsgVBWF();
    MsgVBWF(float forwardAvrSpeed, QString dataStatus);

    //int systemID;
    float forwardAvrSpeed;                 // xx.x = Forward averaged Speed in 1/100 kn (+-50kn)
    QString dataStatus;                    // A = status of data

    static const QString msgSuffix; // = ",,,V,,V,,V";
    static const unsigned long VBWFhash = 4347718;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgVBWF *clone() {return new MsgVBWF(*this);}
};

#endif
