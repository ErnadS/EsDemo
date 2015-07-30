#include "nmea/nmea_message.h"

#ifndef MSG_VER_H
#define MSG_VER_H

class MsgVER : public NmeaMessage
{
public:
    MsgVER();
    MsgVER(int totalNumberOfSentences, int sentenceNumber, QString deviceType,
           QString venderID, QString uniqueIdentifier, QString manufacturerSerialNumber,
           QString modelCode, QString softwareRevision, QString hardwareRevision,
           int sequentialMessageIdentifier);

    int totalNumberOfSentences;
    int sentenceNumber;
    QString deviceType;
    QString venderID;
    QString uniqueIdentifier;
    QString manufacturerSerialNumber;
    QString modelCode;
    QString softwareRevision;
    QString hardwareRevision;
    int sequentialMessageIdentifier;

    static const unsigned long VERhash = 5653842;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgVER *clone() {return new MsgVER(*this);}
};

#endif
