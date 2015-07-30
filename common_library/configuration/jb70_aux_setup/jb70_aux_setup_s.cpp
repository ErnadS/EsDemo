#include "jb70_aux_setup_s.h"


QString JB70_Aux_Setup_S::getAuxName() const
{
    return auxName;
}

void JB70_Aux_Setup_S::setAuxName(const QString &value)
{
    auxName = value;
}

QString JB70_Aux_Setup_S::getFunctionName() const
{
    return functionName;
}

void JB70_Aux_Setup_S::setFunctionName(const QString &value)
{
    functionName = value;
}

QString JB70_Aux_Setup_S::getPinName() const
{
    return pinName;
}

void JB70_Aux_Setup_S::setPinName(const QString &value)
{
    pinName = value;
}

int JB70_Aux_Setup_S::getPinNumber() const
{
    return pinNumber;
}

void JB70_Aux_Setup_S::setPinNumber(int value)
{
    pinNumber = value;
}

int JB70_Aux_Setup_S::getAuxDirection() const
{
    return auxDirection;
}

void JB70_Aux_Setup_S::setAuxDirection(int value)
{
    auxDirection = value;
}
JB70_Aux_Setup_S::JB70_Aux_Setup_S(QObject *parent) :
    QObject(parent)
{
}

JB70_Aux_Setup_S::JB70_Aux_Setup_S(QString auxName, QString functionName, QString pinName,
                                   int pinNumber, int auxDirection):
    QObject(0)
{
    this->auxName       = auxName;
    this->functionName  = functionName;
    this->pinName       = pinName;
    this->pinNumber     = pinNumber;
    this->auxDirection  = auxDirection;
}

JB70_Aux_Setup_S::JB70_Aux_Setup_S(const JB70_Aux_Setup_S &originalValue):
    QObject(0)
{
    *this = originalValue;
}

JB70_Aux_Setup_S &JB70_Aux_Setup_S::operator =(const JB70_Aux_Setup_S &newValue)
{
    this->auxName       = newValue.auxName;
    this->functionName  = newValue.functionName;
    this->pinName       = newValue.pinName;
    this->pinNumber     = newValue.pinNumber;
    this->auxDirection  = newValue.auxDirection;
    return *this;
}
