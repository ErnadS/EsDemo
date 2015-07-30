#ifndef MSG_DDC_H
#define MSG_DDC_H

// Standard Sentence:
// ***********************************************************
// DDC    (4800 baud)
//        1 2  3 4
//        | |  | |
// $--DDC,a,xx,a,a*hh
// 1) Display dimming preset ('D' = Day time setting, 'K' = Dusk setting, 'N' = Night time setting, 'O' = Backlighting off setting)
// 2) Brightness percentage  (00 to 99)
// 3) Coulor palette         ('D' = Day time setting, 'K' = Dusk setting, 'N' = Night time setting, 'O' = Backlighting off setting)
// 4) Sentence Status Flag   ('R' = raport of current settings, 'C' = command

#include "nmea/nmea_message.h"

class MsgDDC : public NmeaMessage
{
public:
    MsgDDC();

    MsgDDC(QString dispDimmPreset, quint8 brightnes, QString coulorPalette, QString statusFlag);

    QString     dispDimmPreset;
    int         brightnes;
    QString     coulorPalette;
    QString     statusFlag;

    static const unsigned long DDChash = 4473923;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgDDC *clone() {return new MsgDDC(*this);}
};

#endif
