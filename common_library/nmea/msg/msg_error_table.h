#ifndef MSG_ERROR_TABLE_H
#define MSG_ERROR_TABLE_H

#include "nmea/nmea_message.h"

class MsgERRORTABLE : public NmeaMessage
{
public:
    MsgERRORTABLE();
    MsgERRORTABLE(QList<unsigned> errorIDs, QList<unsigned> errorCounts);

    QList<unsigned> errorIDs;
    QList<unsigned> errorCounts;

    static const unsigned long ERRORTABLEhash = 4344901;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgERRORTABLE * clone() {return new MsgERRORTABLE(*this);}
};

#endif

