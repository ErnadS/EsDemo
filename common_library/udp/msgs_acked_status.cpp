#include "msgs_acked_status.h"

#include <QDateTime>
quint64 MsgsAckedStatus::expiryTime = 5000; // 5 seconds

bool MsgsAckedStatus::isExpired(int msgNr)
{
    return ((QDateTime::currentMSecsSinceEpoch() - msgUnackedTime[msgNr]) > expiryTime);
}

MsgsAckedStatus::MsgsAckedStatus()
{
    ackRequiredMsgTypes = QList<QString>();
    pairedDevices = QList<QString>();

    msgAckedStatus = QList<bool>();
    msgUnackedTime = QList<quint64>();
    msgAckedData = QList<QList<bool> >();
}

int MsgsAckedStatus::msgNumber(QString msgType)
{
    return ackRequiredMsgTypes.indexOf(msgType);
}

int MsgsAckedStatus::deviceNumber(QString pairedDevice)
{
    return pairedDevices.indexOf(pairedDevice);
}

void MsgsAckedStatus::ackMsg(QString msgType, QString pairedDevice)
{
    int msgNr = msgNumber(msgType);
    int deviceNr = deviceNumber(pairedDevice);

    if((msgNr == -1) || (deviceNr == -1))
        return;

    msgAckedData[deviceNr][msgNr] = true;
    for(int i = 0; i < msgAckedData.length(); i++)
    {
        if(msgAckedData[i][msgNr] == false)
            return;
    }

    msgAckedStatus[msgNr] = true;
}

void MsgsAckedStatus::ackMsgList(QList<QString> msgTypeList, QString pairedDevice)
{
    for(int i = 0; i < msgTypeList.length(); i++)
        ackMsg( msgTypeList[i], pairedDevice);
}

void MsgsAckedStatus::resetMsgAcked(QString msgType)
{
    int msgNr = msgNumber(msgType);

    if(msgNr == -1)
        return;

    msgAckedStatus[msgNr] = false;
    msgUnackedTime[msgNr] = QDateTime::currentMSecsSinceEpoch();

    for(int i = 0; i < msgAckedData.length(); i++)
        msgAckedData[i][msgNr] = false;
}

void MsgsAckedStatus::resetMsgListAcked(QList<QString> msgTypeList)
{
    for(int i = 0; i < msgTypeList.length(); i++)
        resetMsgAcked( msgTypeList[i]);
}

void MsgsAckedStatus::setMsgAcked(int msgNr)
{
    if(msgNr == -1)
        return;
    for(int i = 0; i < msgAckedData.length(); i++)
        msgAckedData[i][msgNr] = true;

    msgAckedStatus[msgNr] = true;
}

void MsgsAckedStatus::setMsgAcked(QString msgType)
{
    setMsgAcked(msgNumber(msgType));
}

void MsgsAckedStatus::setMsgListAcked(QList<QString> msgTypeList)
{
    for(int i = 0; i < msgTypeList.length(); i++)
        setMsgAcked( msgTypeList[i]);
}

bool MsgsAckedStatus::getMessageAcked(QString msgType)
{
    int msgNr = msgNumber(msgType);

    if(msgNr == -1)
        return true;
    else
        return msgAckedStatus[msgNr];
}

bool MsgsAckedStatus::messageNeedsAck(QString msgType)
{
    return (ackRequiredMsgTypes.indexOf(msgType) != -1);
}

void MsgsAckedStatus::addPairedDevice(QString pairedSfi)
{
    if(deviceNumber(pairedSfi) != -1)
        return;

    pairedDevices.append(pairedSfi);
    pairedDevDisconnectCounter.append(0);

    QList<bool> newDeviceAcks;

    for(int i = 0; i < ackRequiredMsgTypes.length(); i++)
        newDeviceAcks.append(true);

    msgAckedData.append(newDeviceAcks);
}

void MsgsAckedStatus::removePairedDevice(QString pairedSfi)
{
    int deviceNr = deviceNumber(pairedSfi);
    if(deviceNr == -1)
        return;

    pairedDevices.removeAt(deviceNr);
    msgAckedData.removeAt(deviceNr);
    pairedDevDisconnectCounter.removeAt(deviceNr);
}

void MsgsAckedStatus::addAckRequiredMsgType(QString fullType)
{
    if(msgNumber(fullType) != -1)
        return;

    ackRequiredMsgTypes.append(fullType);
    msgAckedStatus.append(true);
    msgUnackedTime.append(0);

    for(int i = 0; i < msgAckedData.length(); i++)
        msgAckedData[i].append(true);
}

void MsgsAckedStatus::removeAckRequiredMsgType(QString fullType)
{
    int msgNr = msgNumber(fullType);
    if(msgNr == -1)
        return;

    ackRequiredMsgTypes.removeAt(msgNr);
    msgAckedStatus.removeAt(msgNr);
    msgUnackedTime.removeAt(msgNr);

    for(int i = 0; i < msgAckedData.length(); i++)
        msgAckedData[i].removeAt(msgNr);
}

void MsgsAckedStatus::increaseDisconnectCounters()
{
    QList<QString> disconnect;
    for(int i = 0; i < pairedDevDisconnectCounter.length(); i++)
    {
        pairedDevDisconnectCounter[i]++;

        if(pairedDevDisconnectCounter[i] > 60)
            disconnect.append(pairedDevices[i]);
    }

    for(int i = 0; i < disconnect.length(); i++)
        removePairedDevice(disconnect[i]);
}

void MsgsAckedStatus::resetDisconnectCounter(QString pairedSfi)
{
    int deviceNr = deviceNumber(pairedSfi);
    if(deviceNr == -1)
        return;

    pairedDevDisconnectCounter[deviceNr] = 0;
}
