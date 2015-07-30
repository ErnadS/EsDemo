#ifndef CU_M_001_SETUP_S_H
#define CU_M_001_SETUP_S_H

#include <QObject>
#include "configuration/serialization_controller.h"

class CU_M_001_Setup_S : public QObject
{
    Q_OBJECT

    int         screenOrientation;
    int         systemType;
    QString     ipAddress;
    QString     localID;
    QString     pairedID;
    QString     group;
    QString     remoteDimmDdc;
    int         seccondSystemType;
    bool        seccondystemMenu;
    int         thirdSystemType;
    bool        thirdSystemMenu;
    QString     softwareUpdate;

    int vesselIndex;

    int     unitsDepth;
    int     unitsSpeed;

    QString unitName;
    int     serialNumber;

    Q_PROPERTY(int         screenOrientation READ getScreenOrientation WRITE setScreenOrientation)
    Q_PROPERTY(int         systemType        READ getSystemType        WRITE setSystemType)
    Q_PROPERTY(QString     ipAddress         READ getIpAddress         WRITE setIpAddress)
    Q_PROPERTY(QString     localID           READ getLocalID           WRITE setLocalID)
    Q_PROPERTY(QString     pairedID          READ getPairedID          WRITE setPairedID)
    Q_PROPERTY(QString     group             READ getGroup             WRITE setGroup)
    Q_PROPERTY(QString     remoteDimmDdc     READ getRemoteDimmDdc     WRITE setRemoteDimmDdc)
    Q_PROPERTY(int         seccondSystemType READ getSeccondSystemType WRITE setSeccondSystemType)
    Q_PROPERTY(bool        seccondystemMenu  READ getSeccondystemMenu  WRITE setSeccondystemMenu)
    Q_PROPERTY(int         thirdSystemType   READ getThirdSystemType   WRITE setThirdSystemType)
    Q_PROPERTY(bool        thirdSystemMenu   READ getThirdSystemMenu   WRITE setThirdSystemMenu)
    Q_PROPERTY(QString     softwareUpdate    READ getSoftwareUpdate    WRITE setSoftwareUpdate)

    Q_PROPERTY(int         vesselIndex       READ getVesselIndex       WRITE setVesselIndex)

    Q_PROPERTY(int unitsDepth    READ getUnitsDepth WRITE setUnitsDepth)
    Q_PROPERTY(int unitsSpeed    READ getUnitsSpeed WRITE setUnitsSpeed)

    Q_PROPERTY(QString unitName  READ getUnitName   WRITE setUnitName)
    Q_PROPERTY(int serialNumber  READ getSerialNumber       WRITE setSerialNumber)

public:
    explicit CU_M_001_Setup_S(QObject *parent = 0);

    int getScreenOrientation() const;
    void setScreenOrientation(int value);

    int getSystemType() const;
    void setSystemType(int value);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

    QString getLocalID() const;
    void setLocalID(const QString &value);

    QString getPairedID() const;
    void setPairedID(const QString &value);

    QString getGroup() const;
    void setGroup(const QString &value);

    QString getRemoteDimmDdc() const;
    void setRemoteDimmDdc(const QString &value);

    int getSeccondSystemType() const;
    void setSeccondSystemType(int value);

    bool getSeccondystemMenu() const;
    void setSeccondystemMenu(bool value);

    int getThirdSystemType() const;
    void setThirdSystemType(int value);

    bool getThirdSystemMenu() const;
    void setThirdSystemMenu(bool value);

    QString getSoftwareUpdate() const;
    void setSoftwareUpdate(const QString &value);

    int getVesselIndex() const;
    void setVesselIndex(int value);

    int getUnitsDepth() const;
    void setUnitsDepth(int value);

    int getUnitsSpeed() const;
    void setUnitsSpeed(int value);

    QString getUnitName() const;
    void setUnitName(const QString &value);

    int getSerialNumber() const;
    void setSerialNumber(int value);

signals:

public slots:

};

#endif // CU_M_001_SETUP_S_H
