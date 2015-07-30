#include "jb70_aux_setup.h"
#include "default_jb70_aux_setup.h"
#include <QDebug>

void JB70_Aux_Setup::getDefaults()
{
    {
    // Initialize output pins
    //////////////////////////////////////////////////////////////
    // Aux1  -  pin A16, output,   EXT_RST_PA16   ("RESET OUT", "RESET OUT RET")
    // Aux2  -  pin A17, output,   nRELAY_PA17    ("RELAY NC", "RELAY COM", "RELAY NO")
    // Aux3  -  pin A20, output,   nPOW_FAIL_PA20 ("POW FAIL OUT", "POW FAIL RET")
    // Aux4  -  pin A21, input,    EXT_RST_PA21   ("EXT RESET IN", "EXT RESET IN RET")
    /////////////////////////////////////////////////////////////


        QList<QString> auxNames = Default_JB70_Aux_Setup::getAuxNames();
        QList<QString> functionNames = Default_JB70_Aux_Setup::getFunctionNames();
        QList<QString> pinNames = Default_JB70_Aux_Setup::getPinNames();
        QList<int> pinNumbers = Default_JB70_Aux_Setup::getPinNumbers();
        QList<int> pinDirections = Default_JB70_Aux_Setup::getPinDirections();


        for (int i = 0; i < auxNames.length(); i++)
            Jb70Auxes.append(JB70_Aux_Setup_S(auxNames[i], functionNames[i], pinNames[i],
                                              pinNumbers[i],pinDirections[i]));


        writeSetup();
    }
}

void JB70_Aux_Setup::readSetup()
{
    if (!SerializationController::Deserialize(Jb70Auxes, "jb70_aux_setup", "/setup_files/") ||
            Jb70Auxes.isEmpty() )
        getDefaults();
}

void JB70_Aux_Setup::writeSetup()
{
    SerializationController::Serialize(Jb70Auxes, "jb70_aux_setup", "/setup_files/");
}

JB70_Aux_Setup::JB70_Aux_Setup()
{
    readSetup();
    setupReceivedFlag = false;
}

QString JB70_Aux_Setup::getPinName(const int i) const
{
    return Jb70Auxes[i].getPinName();
}


bool JB70_Aux_Setup::getSetupReceivedFlag() const
{
    return setupReceivedFlag;
}

void JB70_Aux_Setup::setSetupReceivedFlag(bool value)
{
    setupReceivedFlag = value;
}

bool JB70_Aux_Setup::loadFromFile(QString fileSuffix)
{
    return SerializationController::Deserialize(Jb70Auxes, "jb70_aux_setup" + fileSuffix, "/setup_files/saved_configs/");
}

bool JB70_Aux_Setup::saveToFile(QString fileSuffix)
{
    return SerializationController::Serialize(Jb70Auxes, "jb70_aux_setup" + fileSuffix, "/setup_files/saved_configs/");
}
void JB70_Aux_Setup::setPinName(const QString &value, const int i)
{
    Jb70Auxes[i].setPinName(value);
    writeSetup();
}

QString JB70_Aux_Setup::getPinNumber(const int i) const
{
    return QString::number(Jb70Auxes[i].getPinNumber());
}

void JB70_Aux_Setup::setPinNumber(int value, const int i)
{
    Jb70Auxes[i].setPinNumber(value);
    writeSetup();
}

QString JB70_Aux_Setup::getAuxDirection(const int i) const
{
    if(Jb70Auxes[i].getAuxDirection() == 0)
        return "Out";
    else
        return "In";
}

int JB70_Aux_Setup::getAuxDirectionInt(const int i) const
{
    return Jb70Auxes[i].getAuxDirection();
}

void JB70_Aux_Setup::setAuxDirection(int value, const int i)
{
    Jb70Auxes[i].setAuxDirection(value);
    writeSetup();
}

QString JB70_Aux_Setup::getAuxName(const int i) const
{
    return Jb70Auxes[i].getAuxName();
}

void JB70_Aux_Setup::setAuxName(const QString &value, const int i)
{
    Jb70Auxes[i].setAuxName(value);
    writeSetup();
}

QString JB70_Aux_Setup::getFunctionName(const int i) const
{
    return Jb70Auxes[i].getFunctionName();
}

void JB70_Aux_Setup::setFunctionName(const QString &value, const int i)
{
    Jb70Auxes[i].setFunctionName(value);
    writeSetup();
}

QString JB70_Aux_Setup::getFunctionName(const QString &auxName) const
{
    int index = -1;

    for (int i = 0; i < Jb70Auxes.length(); i++)
        if(Jb70Auxes[i].getAuxName() == auxName)
        {
            index = i;
            break;
        }

    if(index == -1)
        return "Disabled";

    return Jb70Auxes[index].getFunctionName();
}

void JB70_Aux_Setup::setFunctionName(const QString &value, const QString &auxName)
{
    int index = -1;

    for (int i = 0; i < Jb70Auxes.length(); i++)
        if(Jb70Auxes[i].getAuxName() == auxName)
        {
            index = i;
            break;
        }

    if(index == -1)
        return;

    Jb70Auxes[index].setFunctionName(value);
    writeSetup();
}

QList<QString> JB70_Aux_Setup::getAuxNames() const
{
    QList<QString> result;
    for(int i = 0; i< Jb70Auxes.length(); i++)
        result.append(Jb70Auxes[i].getAuxName());
    return result;
}

void JB70_Aux_Setup::setAuxNames(const QList<QString> &value)
{
    for(int i = 0; i< value.length(); i++)
        Jb70Auxes[i].setAuxName(value[i]);
}

QList<QString> JB70_Aux_Setup::getFunctionNames() const
{
    QList<QString> result;
    for(int i = 0; i< Jb70Auxes.length(); i++)
        result.append(Jb70Auxes[i].getFunctionName());

    return result;
}

void JB70_Aux_Setup::setFunctionNames(const QList<QString> &value)
{
    for(int i = 0; i< value.count(); i++)
        Jb70Auxes[i].setFunctionName(value[i]);
    setupReceivedFlag = true;
    writeSetup();
}

QList<QString> JB70_Aux_Setup::getAuxDirections() const
{
    QList<QString> result;
    for(int i = 0; i< Jb70Auxes.length(); i++)
        result.append(getAuxDirection(i));
    return result;
}

int JB70_Aux_Setup::getAuxCount() const
{
    return Jb70Auxes.length();
}

