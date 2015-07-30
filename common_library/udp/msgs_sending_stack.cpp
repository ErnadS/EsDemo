#include "msgs_sending_stack.h"

QString msgsSendingStack::getFullType(NmeaMessage *msg)
{
    QString basicType = msg->messageType();

    if(basicType == "ICM")
    {
        MsgICM* icmMsg = static_cast<MsgICM*>(msg);
        basicType += QString::number(icmMsg->commandID);
    }
    else if(basicType == "IDM")
    {
        MsgICM* idmMsg = static_cast<MsgICM*>(msg);
        basicType += QString::number(idmMsg->commandID);
    }
    return basicType;
}

QString msgsSendingStack::getListFullType(QList<NmeaMessage *> msgList)
{
    QString resultType = "";
    for(int i = 0; i < msgList.length(); i++)
        resultType += getFullType(msgList[i]);

    return resultType;
}

void msgsSendingStack::removeSingleFromStack(QString msgFullType)
{
    for(int i = 0; i < singleMsgList.length(); i++)
    {
        if(getFullType(singleMsgList[i]) == msgFullType)
        {
            delete singleMsgList[i];
            singleMsgList.removeAt(i);
        }
    }
}

void msgsSendingStack::removeGroupFromStack(QString msgFullType)
{
    for(int i = 0; i < groupMsgList.length(); i++)
    {
        if(getListFullType(groupMsgList[i]) == msgFullType)
        {
            removeGroupFromStack(i);
        }
    }
}

void msgsSendingStack::removeGroupFromStack(int stackedGroupIndex)
{
    for(int i = 0; i < groupMsgList[stackedGroupIndex].length(); i++)
    {
        delete groupMsgList[stackedGroupIndex][i];
    }
    groupMsgList.removeAt(stackedGroupIndex);
}

msgsSendingStack::msgsSendingStack()
{
    singleMsgList = QList<NmeaMessage*>();
    groupMsgList = QList<QList<NmeaMessage*> >();
}

void msgsSendingStack::addSingleTostack(NmeaMessage *nmeaMsg)
{
    QString msgType = getFullType(nmeaMsg);

    for(int i = 0; i < singleMsgList.length(); i++)
    {
        if(getFullType(singleMsgList[i]) == msgType)
        {
            delete singleMsgList[i];
            singleMsgList[i] = nmeaMsg;
            nmeaMsg = 0;
            return;
        }
    }
    singleMsgList.append(nmeaMsg);
}

void msgsSendingStack::addGroupTostack(QList<NmeaMessage *> nmeaMsgList)
{
    QString listType = getListFullType(nmeaMsgList);

    for(int i = 0; i < groupMsgList.length(); i++)
    {
        if(getListFullType(groupMsgList[i]) == listType)
        {
            for(int j = 0; j < groupMsgList[i].length(); j++)
            {
                delete groupMsgList[i][j];
                groupMsgList[i][j] = nmeaMsgList[j];
                nmeaMsgList[j] = 0;
            }
            return;
        }
    }
    groupMsgList.append(nmeaMsgList);
}

void msgsSendingStack::removeFromStack(QString msgFullType, bool groupMsg)
{
    if(groupMsg)
        removeGroupFromStack(msgFullType);
    else
        removeSingleFromStack(msgFullType);
}
