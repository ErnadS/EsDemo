#ifndef MSG_STL_H
#define MSG_STL_H

#include "nmea/nmea_message.h"

class MsgSTL : public NmeaMessage
{
public:
    MsgSTL();
    MsgSTL(float tripValue, float totalValue);

    float tripValue;
    float totalValue;

    static const unsigned long STLhash = 5461068;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSTL * clone() {return new MsgSTL(*this);}
};

#endif
