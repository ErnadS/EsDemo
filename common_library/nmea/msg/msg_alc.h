//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ALC – Alert Cyclic list (NMEA_IEC 61924-2Edition 1 2012-12, page 139)
//          1   2   3   4    5    6    7    8              4*n  4*n+1  4*n+2 4*n+3  4*n+4
//          |   |   |   |    |    |    |    |                |     |      |     |    |
// $--ALC, xx, xx, xx, x.x, aaa, x.x, x.x, x.x,............, aaa,  x.x,   x.x,  x.x*hh<CR><LF>
// 1) Total number of sentences for this message, 01 – 99
// 2) Sentence number, 01 to 99
// 3) Sequential message identifier, 00 to 99 ( sentences with same sequential message identifier make up one message)
// 4) Number of alert entries transported within the sentence
// 5) Manufacturer mnemonic code, entry 1
// 6) Alert identifier, entry 1
// 7) Alert instance, entry 1
// 8) Revision couter, entry 1
//             .
//             .
//             .
// 4*n) Manufacturer mnemonic code, entry n
// 4*n+1) Alert identifier, entry n
//        4*n+2) Alert instance, entry n
// 4*n+3) Revision counter, entry n
// 4*n+4) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ALC_H
#define MSG_ALC_H

#include "nmea/nmea_message.h"

class MsgSingleALC
{
public:
    MsgSingleALC();
    MsgSingleALC(QString manufacturerMnemonicCode, int alertIdendtifyer, int alertInstance, int revisionCounter);


    QString manufacturerMnemonicCode;
    int alertIdendtifyer;
    int alertInstance;
    int revisionCounter;


    QString getEntryBuffer();
};

class MsgALC : public NmeaMessage
{
public:
    MsgALC();

    int totalNumberOfSentences;

    QList<MsgSingleALC> sentenceList;

    void addSentence(const MsgSingleALC& sentence);

    bool setParams(QStringList m_message_parameters);

    static const unsigned long ALChash = 4279363;

    QString getMsgBuffer();

    MsgALC * clone() {return new MsgALC(*this);}
};


#endif
