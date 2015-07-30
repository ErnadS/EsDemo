//////////////////////////////////////////////////////////////
// Standard Sentence:
// ***********************************************************
// ACN – Alert command (NMEA_IEC 61924-2Edition 1 2012-12, page 138)
//              1      2    3    4   5  6 7
//              |      |    |    |   |  | |
// $--ACN, hhmmss.ss, aaa, x.x, x.x, c, a*hh<CR><LF>
// 1) Time (Release time of the alert command)
// 2) Manufacturer mnemonic code (for proprietary alerts defined by manufacturer, for standard alerts should be a null field)
// 3) Alert identifier (3-7 digit integer, 10000-9999999 reserved for proprietary alerts)
// 4) Alert instance, 1 to 999999 ( identifies current instance of the alert zo distinguish alerts of the same type and from
//    the same source)
// 5) Alert command, A, Q, O or S ( This should not be a null field; A – acknowledge, Q request/repeat information,
//    O – responsibility transfer, S – silence)
// 6) Sentence status flag ( Should be „C“ and should not be null field. C indicates a command, sentence without C is not a command.)
// 7) Checksum
//////////////////////////////////////////////////////////////

#ifndef MSG_ACM_H
#define MSG_ACM_H

#include "nmea/nmea_message.h"

class MsgACN : public NmeaMessage
{
public:
    MsgACN();
    MsgACN(QString timeOfAlert, QString manufacturerMnemonicCode, unsigned long alertIdentifier, unsigned long alertInstance,
           QString alertCommand, QString alertStatusFlag);

    QString timeOfAlert;
    QString manufacturerMnemonicCode;
    unsigned long alertIdentifier;
    unsigned long alertInstance;
    QString alertCommand;
    QString alertStatusFlag;

    static const unsigned long ACNhash = 4277070; //4277069;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgACN * clone() {return  new MsgACN(*this);}
};

#endif
