//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// DPT Water depth relative to the transducer
//            1      2  3 4  5   6
//            |      |  | |  |   |
// $--DPT,DATA_METRES,,OFFSET_METRES, MAXIMUM_METRES*hh
// 1) Water depth relative to the transducer
// 2) The depth offset of the transducer
// 3) Maximum depth that the sounder can detect a sea-bed
// 4) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_DPT_H
#define MSG_DPT_H

#include "nmea/nmea_message.h"

class MsgDPT : public NmeaMessage
{
public:
    MsgDPT();
    MsgDPT(float waterDepth, float transducerOffset, float maximumDepth);


    float waterDepth;                      // Water depth relative to the transducer
    float transducerOffset;                // The depth offset of the transducer
    float maximumDepth;                    // Maximum depth that the sounder can detect a sea-bed

    static const unsigned long DPThash = 4477012;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgDPT * clone() {return new MsgDPT(*this);}
};

#endif
