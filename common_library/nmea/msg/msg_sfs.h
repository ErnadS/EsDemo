#ifndef MSG_SFS_H
#define MSG_SFS_H

#include "nmea/nmea_message.h"

class MsgSFS : public NmeaMessage
{
public:
    MsgSFS();
    MsgSFS(QString simCommand, float speedLong, float speedTrans);

    QString simCommand;
    float speedLong;
    float speedTrans;


    static const unsigned long SFShash = 5457491;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgSFS * clone() {return new MsgSFS(*this);}
};

#endif
