#include "jb70_aux_handler_setup_s.h"


bool JB70_Aux_Handler_Setup_S::getSpeedPulseOutputSTW() const
{
    return speedPulseOutputSTW;
}

void JB70_Aux_Handler_Setup_S::setSpeedPulseOutputSTW(bool value)
{
    speedPulseOutputSTW = value;
}

int JB70_Aux_Handler_Setup_S::getPulsesPerMile() const
{
    return pulsesPerMile;
}

void JB70_Aux_Handler_Setup_S::setPulsesPerMile(int value)
{
    pulsesPerMile = value;
}
JB70_Aux_Handler_Setup_S::JB70_Aux_Handler_Setup_S(QObject *parent) :
    QObject(parent)
{
}
