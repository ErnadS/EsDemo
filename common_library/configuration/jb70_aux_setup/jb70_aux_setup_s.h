#ifndef JB70_AUX_SETUP_S_H
#define JB70_AUX_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class JB70_Aux_Setup_S : public QObject
{
    Q_OBJECT
    
    QString      auxName;
    QString      functionName;

    QString      pinName;
    int          pinNumber;
    int          auxDirection;
    
    Q_PROPERTY(QString      auxName           READ getAuxName           WRITE setAuxName)
    Q_PROPERTY(QString      functionName      READ getFunctionName      WRITE setFunctionName)
    Q_PROPERTY(QString      pinName           READ getPinName           WRITE setPinName)
    Q_PROPERTY(int          pinNumber         READ getPinNumber         WRITE setPinNumber)
    Q_PROPERTY(int          auxDirection      READ getAuxDirection      WRITE setAuxDirection)

public:
    explicit JB70_Aux_Setup_S(QObject *parent = 0);

    JB70_Aux_Setup_S(QString auxName, QString functionName, QString pinName, int pinNumber,
                     int auxDirection);
    JB70_Aux_Setup_S(const JB70_Aux_Setup_S& originalValue);

    JB70_Aux_Setup_S& operator = (const JB70_Aux_Setup_S &newValue);

    QString getAuxName() const;
    void setAuxName(const QString &value);

    QString getFunctionName() const;
    void setFunctionName(const QString &value);

    QString getPinName() const;
    void setPinName(const QString &value);

    int getPinNumber() const;
    void setPinNumber(int value);

    int getAuxDirection() const;
    void setAuxDirection(int value);


signals:

public slots:

};

#endif // JB70_AUX_SETUP_S_H
