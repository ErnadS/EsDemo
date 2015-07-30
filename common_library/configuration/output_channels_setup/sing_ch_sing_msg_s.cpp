#include "sing_ch_sing_msg_s.h"

QString Sing_Ch_Sing_Msg_S::getMsgType() const
{
    return msgType;
}

void Sing_Ch_Sing_Msg_S::setMsgType(const QString &value)
{
    msgType = value;
}

bool Sing_Ch_Sing_Msg_S::getEnabled() const
{
    return enabled;
}

void Sing_Ch_Sing_Msg_S::setEnabled(bool value)
{
    enabled = value;
}

bool Sing_Ch_Sing_Msg_S::getAllowed() const
{
    return allowed;
}

void Sing_Ch_Sing_Msg_S::setAllowed(bool value)
{
    allowed = value;
}
Sing_Ch_Sing_Msg_S::Sing_Ch_Sing_Msg_S(QObject *parent) :
    QObject(parent)
{
}

Sing_Ch_Sing_Msg_S::Sing_Ch_Sing_Msg_S(QString msgType, bool enabled, bool allowed) :
    QObject(0)
{
    this->msgType = msgType;
    this->enabled = enabled;
    this->allowed = allowed;
}

Sing_Ch_Sing_Msg_S::Sing_Ch_Sing_Msg_S(const Sing_Ch_Sing_Msg_S &originalValue) :
    QObject(0)
{
    *this = originalValue;
}

Sing_Ch_Sing_Msg_S &Sing_Ch_Sing_Msg_S::operator =(const Sing_Ch_Sing_Msg_S &newValue)
{
    this->msgType = newValue.msgType;
    this->enabled = newValue.enabled;
    this->allowed = newValue.allowed;
    return *this;

}
