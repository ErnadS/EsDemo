#include "jb70_aux_handler_setup.h"

void JB70_Aux_Handler_Setup::readSetup()
{
    if (!SerializationController::Deserialize(auxHandlerSetup, "jb70_aux_handler_setup", "/setup_files/"))
    {
        auxHandlerSetup.setSpeedPulseOutputSTW(true);
        auxHandlerSetup.setPulsesPerMile(200);

        writeSetup();
    }
}

void JB70_Aux_Handler_Setup::writeSetup()
{
    SerializationController::Serialize(auxHandlerSetup, "jb70_aux_handler_setup", "/setup_files/");
}

JB70_Aux_Handler_Setup::JB70_Aux_Handler_Setup()
{
    readSetup();
}

bool JB70_Aux_Handler_Setup::getSpeedPulseOutputSTW() const
{
    return auxHandlerSetup.getSpeedPulseOutputSTW();
}

void JB70_Aux_Handler_Setup::setSpeedPulseOutputSTW(bool value)
{
    auxHandlerSetup.setSpeedPulseOutputSTW(value);
    writeSetup();
}

int JB70_Aux_Handler_Setup::getPulsesPerMile() const
{
    return auxHandlerSetup.getPulsesPerMile();
}

void JB70_Aux_Handler_Setup::setPulsesPerMile(int value)
{
    auxHandlerSetup.setPulsesPerMile(value);
    writeSetup();
}

bool JB70_Aux_Handler_Setup::loadFromFile(QString fileSuffix)
{
    //saved_configs/
    return SerializationController::Deserialize(auxHandlerSetup, "jb70_aux_handler_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool JB70_Aux_Handler_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(auxHandlerSetup, "jb70_aux_handler_setup" + fileSuffix, "/setup_files/saved_configs/");
}
