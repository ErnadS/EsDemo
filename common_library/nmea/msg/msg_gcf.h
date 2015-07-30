//////////////////////////////////////////////////////////////
// Skipper Sentence:
// ***********************************************************
// GCF   Get Configuratio (used by Service Sogtware)
//
// $PSKPSCF,*hh
//////////////////////////////////////////////////////////////

#ifndef MSG_GCF_H
#define MSG_GCF_H

#include "nmea/nmea_message.h"


class MsgGCF : public NmeaMessage
{
public:
    MsgGCF();

    static const unsigned long GCFhash = 4670278;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgGCF * clone() {return new MsgGCF(*this);}
};

#endif
