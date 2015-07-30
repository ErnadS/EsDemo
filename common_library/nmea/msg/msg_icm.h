//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// ICM   Internal communication message
//          1 2 3     n
//          | | |     |
// $PSKPICM,x,x,x,...,x*hh
// 1) Message version (to disable different message parsing on sending an receiving sides)
// 2) Command ID
// 3) - n) message parameters
//////////////////////////////////////////////////////////////

#ifndef MSG_ICM_H
#define MSG_ICM_H

#include "nmea/nmea_message.h"

class MsgICM : public NmeaMessage
{
public:
    MsgICM();
    MsgICM(int commandID, QList<int> msgParameters);

    int messageVersion;
    int commandID;
    QList<int> msgParameters;

    static const unsigned long ICMhash = 4801357;

    static const int msgVersion = 0;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgICM * clone() {return new MsgICM(*this);}
};

#endif
