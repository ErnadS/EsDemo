#ifndef SING_CH_SING_MSG_S_H
#define SING_CH_SING_MSG_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class Sing_Ch_Sing_Msg_S : public QObject
{
    Q_OBJECT

    QString msgType;
    bool enabled;
    bool allowed;

    Q_PROPERTY(QString msgType READ getMsgType WRITE setMsgType)
    Q_PROPERTY(bool enabled    READ getEnabled WRITE setEnabled)
    Q_PROPERTY(bool allowed    READ getAllowed WRITE setAllowed)
public:
    explicit Sing_Ch_Sing_Msg_S(QObject *parent = 0);
    Sing_Ch_Sing_Msg_S(QString msgType, bool enabled, bool allowed);

    Sing_Ch_Sing_Msg_S(const Sing_Ch_Sing_Msg_S& originalValue);

    Sing_Ch_Sing_Msg_S& operator = (const Sing_Ch_Sing_Msg_S &newValue);


    QString getMsgType() const;
    void setMsgType(const QString &value);

    bool getEnabled() const;
    void setEnabled(bool value);

    bool getAllowed() const;
    void setAllowed(bool value);

signals:

public slots:

};

#endif // SING_CH_SING_MSG_S_H
