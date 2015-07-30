#ifndef JB70_AUX_HANDLER_SETUP_H
#define JB70_AUX_HANDLER_SETUP_H

#include "jb70_aux_handler_setup_s.h"

class JB70_Aux_Handler_Setup
{
    JB70_Aux_Handler_Setup_S auxHandlerSetup;


    void readSetup();
    void writeSetup();
public:
    JB70_Aux_Handler_Setup();

    bool getSpeedPulseOutputSTW() const;
    void setSpeedPulseOutputSTW(bool value);

    int getPulsesPerMile() const;
    void setPulsesPerMile(int value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
};

#endif // JB70_AUX_HANDLER_SETUP_H
