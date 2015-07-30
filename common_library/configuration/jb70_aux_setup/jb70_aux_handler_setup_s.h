#ifndef JB70_AUX_HANDLER_SETUP_S_H
#define JB70_AUX_HANDLER_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class JB70_Aux_Handler_Setup_S : public QObject
{
    Q_OBJECT

    bool speedPulseOutputSTW;
    int pulsesPerMile;

    Q_PROPERTY(bool speedPulseOutputSTW READ getSpeedPulseOutputSTW WRITE setSpeedPulseOutputSTW )
    Q_PROPERTY(int pulsesPerMile READ getPulsesPerMile WRITE setPulsesPerMile )

public:
    explicit JB70_Aux_Handler_Setup_S(QObject *parent = 0);

    bool getSpeedPulseOutputSTW() const;
    void setSpeedPulseOutputSTW(bool value);

    int getPulsesPerMile() const;
    void setPulsesPerMile(int value);

signals:

public slots:

};

#endif // JB70_AUX_HANDLER_SETUP_S_H
