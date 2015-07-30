//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// PNG   Ping on request
//          1 2
//          | |
// $PSKPPNG,x*hh
// 1) SYSTEM ID (2)  2=DL2 Master
// 2) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_PNG_H
#define MSG_PNG_H

#include "nmea/nmea_message.h"

class MsgPNG : public NmeaMessage
{
public:
    MsgPNG();
    MsgPNG(int systemID);

    int systemID;

    static const unsigned long PNGhash = 5262919;
    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgPNG * clone() {return new MsgPNG(*this);}
};

#endif
