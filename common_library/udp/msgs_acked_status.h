#ifndef MSGS_ACKED_STATUS_H
#define MSGS_ACKED_STATUS_H

#include <QList>
#include "nmea/nmea_message.h"
#include "nmea/nmea_include.h"

class MsgsAckedStatus
{
public:
    MsgsAckedStatus();

    QList<QString> ackRequiredMsgTypes;
    QList<QString> pairedDevices;
    QList<int> pairedDevDisconnectCounter;

    QList<bool> msgAckedStatus;
    QList<quint64> msgUnackedTime;
    QList<QList<bool> > msgAckedData;

    static quint64 expiryTime;

    int msgNumber(QString msgType);
    int deviceNumber(QString pairedDevice);

    void ackMsg(QString msgType, QString pairedDevice);
    void ackMsgList(QList<QString> msgTypeList, QString pairedDevice);

    void resetMsgAcked(QString msgType);
    void resetMsgListAcked(QList<QString> msgTypeList);

    void setMsgAcked(QString msgType);
    void setMsgListAcked(QList<QString> msgTypeList);

    bool getMessageAcked(QString msgType);
    bool messageNeedsAck(QString msgType);
    void setMsgAcked(int msgNr);

    bool isExpired(int msgNr);

    void addPairedDevice(QString pairedSfi);
    void removePairedDevice(QString pairedSfi);

    void addAckRequiredMsgType(QString fullType);
    void removeAckRequiredMsgType(QString fullType);

    void increaseDisconnectCounters();
    void resetDisconnectCounter(QString pairedSfi);
};

#endif
