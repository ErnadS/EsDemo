//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// BLK   Blanking Mode
//          1 2 3
//          | | |
// $PSKPBLK,x,x*hh
// 1) SYSTEM ID (2)  2=DL2 Master
// 2) Pinging on or off (1 or 0)
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_BLNK_H
#define MSG_BLNK_H

#include "nmea/nmea_message.h"

class MsgBLNK : public NmeaMessage
{
public:
    MsgBLNK();
    MsgBLNK(int systemID, QString pingOnOff);

    int systemID;
    QString pingOnOff;


    static const unsigned long BLNKhash = 5000779;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgBLNK * clone() {return new MsgBLNK(*this);}
};

#endif
