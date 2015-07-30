#include "update_from_usb.h"
#ifdef SYSTEM_JB70
    #include "logger.h"
#endif


void Update_From_USB::connectToLogger()
{
#ifdef SYSTEM_JB70
    connect(&Logger::instance(), SIGNAL(sigDevicePresent()), this, SLOT(slotDeviceDetected()));
#endif
}

Update_From_USB::Update_From_USB(QObject *parent) :
    QObject(parent)
{
    mainNameFilter << "9101_4_SAMA5D3_main";
    uiNameFilter << "ui*";

    mainUpdateDestinationPath = "/opt/version_info/update/9101_4_SAMA5D3_main";
    uiUpdateDestinationPath = "/var/www/ui";
}

void Update_From_USB::slotDeviceDetected()
{
    QDir updates("/media/usb0/update");
    if(updates.exists())
    {
        QFileInfoList mainUpdateInfo = updates.entryInfoList(mainNameFilter);
        QFileInfoList uiUpdateInfo = updates.entryInfoList(uiNameFilter);

        if((mainUpdateInfo.length() != 1) || (uiUpdateInfo.length() != 1))
            return;

        if(QFile::copy(mainUpdateInfo[0].absoluteFilePath(), mainUpdateDestinationPath) == false)
        {
            QFile::remove(mainUpdateDestinationPath);
            return;
        }

        if(QFile::copy(uiUpdateInfo[0].absoluteFilePath(), uiUpdateDestinationPath) == false)
        {
            QFile::remove(mainUpdateDestinationPath);
            QFile::remove(uiUpdateDestinationPath);
            return;
        }
        emit sigUpdateAvailable();
    }
}
