#ifndef CU_M_001_SETUP_H
#define CU_M_001_SETUP_H

#include "cu_m_001_setup_s.h"

class CU_M_001_Setup
{
    CU_M_001_Setup_S CuM001Setup;

    bool setupReceivedFlag;
    QString systemType;

    void readSetup();
    void writeSetup();

public:
    CU_M_001_Setup();

    void setCuM001(int screenOrientation, int systemType, QString ipAddress, QString localID, QString pairedID, QString group,
                   QString remoteDimmDdc, int seccondSystemType, bool seccondystemMenu, int thirdSystemType, bool thirdSystemMenu,
                   QString softwareUpdate, int vesselIndex, int unitsDepth, int unitsSpeed);

    QString getUnitsDepthString() const;
    QString getUnitsSpeedString() const;

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

    bool getSetupReceivedFlag() const;
    void setSetupReceivedFlag(bool value);


    int getUnitsDepth() const;
    void setUnitsDepth(int value);

    int getUnitsSpeed() const;
    void setUnitsSpeed(int value);

    void changeIpAddress(QString newIp = "UseExisting");

    QString getUnitName() const;
    void setUnitName(const QString &value);

    int getSerialNumber() const;
    void setSerialNumber(int value);


    bool loadFromFile(QString fileSuffix);
    bool saveToFile(QString fileSuffix);
    void getDefaults(int level = 0);
};

#endif // CU_M_001_SETUP_H
