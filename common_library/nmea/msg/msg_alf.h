//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ALF – Alert sentence (NMEA_IEC 61924-2Edition 1 2012-12, page 140)
//         1  2  3      4      5  6  7   8    9    10   11  12    13  14
//         |  |  |      |      |  |  |   |    |    |    |   |     |   |
// $--ALF, x, x, x, hhmmss.ss, a, a, a, aaa, x.x, x.x, x.x, x, c---c*hh<CR><LF>
// 1) Total number of sentences for this message, 1-2
// 2) Sentence number, 1-2
// 3) Sequential message identifier, 0-9
// 4) Time of last change ( time of dhe last change of data within the aler message)
// 5) Alert category, A, B or C
// 6) Alert priority, E, A, W or C
// 7) Alert state, A, S, N, O, U or V
// 8) Manufacturer mnemonic code ( for propriatary alerts, for standard should be null field)
// 9) Alert identifier (3-7 digit integer, 10000-9999999 reserved for proprietary alerts)
// 10) Alert instance, 1 to 999999 (identifies current instance of the alert zo distinguish alerts of the same type and from the same source)
// 11) Revision counter, 1 to 99
// 12) Escalation counter, 0 to 9
// 13) Alert text (To transmit additional alert description, optionally second ALF sentence may be transmitted.)
// 14) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ALF_H
#define MSG_ALF_H

#include "nmea/nmea_message.h"

class MsgALF : public NmeaMessage
{
public:
    MsgALF();
    MsgALF(int totalNumberOfSentences, int sentenceNumber, int sequentialMessageIdentifier, QString timeOfLastChange,
           QString alertCategory, QString alertPriority, QString alertState, QString manufacturerMnemonicCode,
           unsigned long alertIdentifier, unsigned long alertInstance, int revisionCounter, int escalationCounter,
           QString text);

    int totalNumberOfSentences;
    int sentenceNumber;
    int sequentialMessageIdentifier;
    QString timeOfLastChange;
    QString alertCategory;
    QString alertPriority;
    QString alertState;

    QString manufacturerMnemonicCode;
    unsigned long alertIdentifier;
    unsigned long alertInstance;
    int revisionCounter;
    int escalationCounter;
    QString alertText;
    QString alertDescription;

    static const unsigned long ALFhash = 4279366;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgALF * clone() {return new MsgALF(*this);}
};

#endif
