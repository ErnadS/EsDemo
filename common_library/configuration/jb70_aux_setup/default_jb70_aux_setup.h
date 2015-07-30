#ifndef DEFAULT_JB70_AUX_SETUP_H
#define DEFAULT_JB70_AUX_SETUP_H

#include <QString>
#include <QList>

class Default_JB70_Aux_Setup
{
    Default_JB70_Aux_Setup();

    static QList<QString> auxNames;
    static QList<QString> functionNames;
    static QList<QString> pinNames;
    static QList<int> pinNumbers;
    static QList<int> pinDirections;

    static QList<QString> inputFunctions;
    static QList<QString> outputFunctions;
public:

    static QList<QString> getAuxNames();
    static QList<QString> getFunctionNames();
    static QList<QString> getPinNames();
    static QList<int> getPinNumbers();
    static QList<int> getPinDirections();

    static QList<QString> getAllowedFunctions(const QString& auxName);


    static QList<QString> getInputFunctions();
    static QList<QString> getOutputFunctions();

    ////////////////////////////////////////
    static int functionNameToInt(QString fName);
    static QString intToFname( int fName);

    static int auxNameToInt(QString aName);
    static QString intToAuxname( int aName);

    static int directionToInt(QString aDirection);
    static QString intToDirection( int aDirection);
};

#endif // DEFAULT_JB70_AUX_SETUP_H
