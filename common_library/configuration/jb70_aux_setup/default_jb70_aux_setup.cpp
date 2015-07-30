#include "default_jb70_aux_setup.h"
#include <QDebug>

#define FUNCTION_ALLOWED            true
#define FUNCTION_NOT_ALLOWED        false


const int auxCount = 4;
const int numberOfInputFunctions = 4;
const int numberOfOutputFunctions = 10;


QList<QString> Default_JB70_Aux_Setup::inputFunctions = QList<QString>()
                                                                                             <<"Alarm acknowledge"
                                                                                             <<"Alarm silence"
                                                                                             <<"Mute in"
                                                                                             <<"Disabled";

bool allowedInput[numberOfInputFunctions][auxCount] = {
    // Aux1                Aux2                  Aux3                  Aux4
    {FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_ALLOWED},     // Alarm acknowledge
    {FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_ALLOWED},     // Alarm silence
    {FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_ALLOWED},     // Mute in
    {FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_ALLOWED}      // Disabled
};


QList<QString> Default_JB70_Aux_Setup::outputFunctions = QList<QString>()
                                                                                        <<"StwPulseOutput"
                                                                                        <<"SogPulseOutput"
                                                                                        <<"AlarmBeepOutput"
                                                                                        <<"AlarmOutput"
                                                                                        <<"FittnesOutput"
                                                                                        <<"PowerFailureOutput"
                                                                                        <<"SpeedLimit"
                                                                                        <<"SynchOut"
                                                                                        <<"Ping out"
                                                                                        <<"Disabled";
bool allowedOutput[numberOfOutputFunctions][auxCount] = {
    // Aux1            Aux2              Aux3              Aux4
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED},     // StwPulseOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED},     // SogPulseOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED},     // AlarmBeepOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED},     // AlarmOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED},     // FittnesOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED},     // PowerFailureOutput
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED},     // SpeedLimit
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED},     // SynchOut
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_NOT_ALLOWED, FUNCTION_NOT_ALLOWED},     // Ping out
    {FUNCTION_ALLOWED, FUNCTION_ALLOWED, FUNCTION_ALLOWED,     FUNCTION_NOT_ALLOWED}      // Disabled
};

QList<QString> Default_JB70_Aux_Setup::auxNames = QList<QString>() <<"Aux1" <<"Aux2" <<"Aux3" <<"Aux4";
QList<QString> Default_JB70_Aux_Setup::functionNames = QList<QString>() <<"StwPulseOutput" <<"AlarmOutput"
                                                                 <<"PowerFailureOutput" <<"Alarm acknowledge";
QList<QString> Default_JB70_Aux_Setup::pinNames = QList<QString>() <<"A20" <<"A16" <<"A17" <<"A21";
QList<int> Default_JB70_Aux_Setup::pinNumbers = QList<int>() <<20 <<16 <<17 <<21;
QList<int> Default_JB70_Aux_Setup::pinDirections = QList<int>() <<0 <<0 <<0 <<1;


Default_JB70_Aux_Setup::Default_JB70_Aux_Setup()
{
}
QList<QString> Default_JB70_Aux_Setup::getOutputFunctions()
{
    return outputFunctions;
}

int Default_JB70_Aux_Setup::functionNameToInt(QString fName)
{
    QList<QString> allFunctions = outputFunctions;
    allFunctions<< inputFunctions;

    return allFunctions.indexOf(fName);
}

QString Default_JB70_Aux_Setup::intToFname(int fName)
{
    QList<QString> allFunctions = outputFunctions;
    allFunctions<< inputFunctions;

    return allFunctions[fName];
}

int Default_JB70_Aux_Setup::auxNameToInt(QString aName)
{
    return auxNames.indexOf(aName);
}

QString Default_JB70_Aux_Setup::intToAuxname(int aName)
{
    return auxNames[aName];
}

int Default_JB70_Aux_Setup::directionToInt(QString aDirection)
{
    if(aDirection == "Out")
        return 0;
    else
        return 1;
}

QString Default_JB70_Aux_Setup::intToDirection(int aDirection)
{
    if(aDirection == 0)
        return "Out";
    else
        return "In";
}

QList<QString> Default_JB70_Aux_Setup::getInputFunctions()
{
    return inputFunctions;
}

QList<int> Default_JB70_Aux_Setup::getPinDirections()
{
    return pinDirections;
}

QList<QString> Default_JB70_Aux_Setup::getAllowedFunctions(const QString &auxName)
{
    QList<QString> result = QList<QString>();

    int index = auxNames.indexOf(auxName);
    if(index == -1)
        return result;

    for (int i = 0; i < numberOfInputFunctions; i++)
        if(allowedInput[i][index])
            result.append(inputFunctions[i]);

    for (int i = 0; i < numberOfOutputFunctions; i++)
        if(allowedOutput[i][index])
            result.append(outputFunctions[i]);

    return result;
}

QList<int> Default_JB70_Aux_Setup::getPinNumbers()
{
    return pinNumbers;
}

QList<QString> Default_JB70_Aux_Setup::getPinNames()
{
    return pinNames;
}

QList<QString> Default_JB70_Aux_Setup::getFunctionNames()
{
    return functionNames;
}

QList<QString> Default_JB70_Aux_Setup::getAuxNames()
{
    return auxNames;
}


