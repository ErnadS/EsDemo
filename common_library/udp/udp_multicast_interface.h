#ifndef UDP_MULTICAST_INTERFACE_H
#define UDP_MULTICAST_INTERFACE_H

#include <QObject>
#include <QTimer>

#include "msgs_acked_status.h"
#include "msgs_sending_stack.h"
#include "udp_61162_450.h"
#include "udp_multicast_creator.h"
#include "nmea/nmea_parser.h"
#include "system_log/error_log/error_counter.h"

class UdpMulticastInterface : public QObject
{
    Q_OBJECT

    UDP_61162_450* udp61162_450;
    QTimer* sendingTimer;

    QString localSfi;
    bool connected;
    MsgsAckedStatus ackedStatus;
    msgsSendingStack sendingStack;

    MsgIDM *getAckMsg(NmeaMessage* msg);
    MsgIDM* getAckMsg(QList<NmeaMessage*> msgList);
    MsgIDM *getAckMsg(QString fullType, bool isGroupMsg);

    void handleAckMsg(MsgIDM* ackMsg, QString msgSource);

    bool isStackedGroupAcked(int stackedGroupIndex);
    bool isStackedMsgAcked(QString msgFullType);

    void checkExpiryTime();

    void handleConnectionRequest(QString sourceSfi, QString msgCommand);


public:
    explicit UdpMulticastInterface(QObject *parent = 0);

    bool init();
    void updateUdpGroup();
    qint64 sendMulticastMsg(QByteArray array);

    void requestConnection();

    static int groupNameToIndex(QString groupName);
    static QString groupIndexToName(int nIndex);


signals:
    void sigNmeaMsgReceived(NmeaMessage* message);
    void sigSendDiagnosticsInfo(QString, QString, NmeaMessage *);

public slots:
    void slotSendSingleMsg(NmeaMessage* message, bool notInStack = true);
    void slotSendListOfMsgs(QList<NmeaMessage*> messageList, bool notInStack = true);
    void slotHandleUdpMulticast(UdpMulticastGroupMsg* udpMulticastGroupMsg);

private slots:
    void sendingTimerTimeout();
};

#endif
