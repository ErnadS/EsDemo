//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// INFO    (for debug, only between our systems)
//          1   2   3
//          |   |   |
// $PSKINFO,x,AAAAA*hh
// 1) SYSTEM ID (2=DL2 card 1. 3=DL2 Slave card2)
// 2) Text information.
// 3) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_INFO_H
#define MSG_INFO_H

#include "nmea/nmea_message.h"
#include <qstring.h>

class MsgINFO : public NmeaMessage
{
public:
    MsgINFO();
    MsgINFO(int systemID, QString information);

    int systemID;
    QString information;
    static const unsigned long INFOhash = 5129807;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgINFO * clone() {return new MsgINFO(*this);}
};

#endif
