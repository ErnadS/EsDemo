#ifndef JB70_AUX_SETUP_H
#define JB70_AUX_SETUP_H

#include "jb70_aux_setup_s.h"
#include "jb70_aux_handler_setup.h"

class JB70_Aux_Setup
{
    QList<JB70_Aux_Setup_S> Jb70Auxes;
    bool setupReceivedFlag;



    void setPinName(const QString &value, const int i);
    void setPinNumber(int value, const int i);
    void setAuxDirection(int value, const int i);

    void readSetup();
    void writeSetup();
public:
    JB70_Aux_Setup();

    QString getPinName(const int i) const;
    QString getPinNumber(const int i) const;
    QString getAuxDirection(const int i) const;
    int getAuxDirectionInt(const int i) const;

    QString getAuxName(const int i) const;
    void setAuxName(const QString &value, const int i);

    QString getFunctionName(const int i) const;
    void setFunctionName(const QString &value, const int i);

    //
    QString getFunctionName(const QString &auxName) const;
    void setFunctionName(const QString &value, const QString &auxName);
    //

    QList<QString> getAuxNames()const;
    void setAuxNames(const QList<QString>& value);

    QList<QString> getFunctionNames()const;
    void setFunctionNames(const QList<QString>& value);

    QList<QString> getAuxDirections()const;

    int getAuxCount()const;

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults();
};

#endif // JB70_AUX_SETUP_H
