#ifndef MSGS_SENDING_STACK_H
#define MSGS_SENDINGS_TACK_H

#include <QList>

#include "nmea/nmea_message.h"
#include "nmea/nmea_include.h"

class msgsSendingStack
{

public:
    msgsSendingStack();

    QList<NmeaMessage*> singleMsgList;
    QList<QList<NmeaMessage*> > groupMsgList;

    QString getFullType(NmeaMessage* msg);
    QString getListFullType(QList<NmeaMessage*> msgList);


    void removeSingleFromStack(QString msgFullType);
    void removeGroupFromStack(QString msgFullType);
    void removeGroupFromStack(int stackedGroupIndex);

    void addSingleTostack(NmeaMessage* nmeaMsg);
    void addGroupTostack(QList<NmeaMessage*> nmeaMsgList);

    void removeFromStack(QString msgFullType, bool groupMsg);
};

#endif
