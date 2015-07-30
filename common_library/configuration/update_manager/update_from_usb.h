#ifndef UPDATE_FROM_USB_H
#define UPDATE_FROM_USB_H

#include <QObject>

#include <QFile>
#include <QDir>

class Update_From_USB : public QObject
{
    Q_OBJECT

    QStringList mainNameFilter;
    QStringList uiNameFilter;

    QString mainUpdateDestinationPath;
    QString uiUpdateDestinationPath;

public:
    explicit Update_From_USB(QObject *parent = 0);

    void connectToLogger();
signals:
    void sigUpdateAvailable();

public slots:
    void slotDeviceDetected();

};

#endif // UPDATE_FROM_USB_H
