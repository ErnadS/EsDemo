//////////////////////////////////////////////////////////////
// Proprietary Sentence:
// ***********************************************************
// CFG    (4800 baud)
//          1 2  3 4  5   6  7 8  9 10 11
//          | |  | |  |   |  | |  | |  |
// $PSKPCFG,x,xx,x,x,xx,AAAA,x,x,xx,x*hh
// 1) SYSTEM ID (2, 3  2 = DL2 Master 3 = DL2 Slave )
// 2) MODE
//      Bit 1(0=Operate 4800 out, 1 = Raw data 115200 out)
//      Bit 2 Frequency selection 0 = 715, 1 = 555 (temporary)
//      NEW:
//      OPERATE, high band = 0; RAW, high band = 1; OPERATE, low band = 2; RAW, low band = 3
// 3) Water track Power level 0-3
// 4) Water track Pulse length 0-3 (1,2,4,8ms)
// 5) Water track Range offset in x*0.5m (1-31) (0.5-16.5m)
// 6) Formats ABCD
//      A = DAT
//      B = VBWF
//      C = MTWF
//      D = ALMA
// 7) Bottomr track Power level 0-3
// 8) Bottom track Pulse length 0-3 (1,2,4,8ms)
// 9) Bottom track Range offset in x*0.5m (1-31) (0.5-16.5m)
// 10) Ping mode
//      0 = Use Bottom ping for both STW and SOG
//      1 = Use separate ping for STW and SOG
//      2 = Ping only for STW
//      3 = Ping only for SOG
//      4 = Ping on request (when $PSKPPNG is sent)
//      5 = Stop pinging on request.
//         ($PSKPBLK,0 = off) ($PSKPBLK,1 = resume)
// 11) Checksum
//////////////////////////////////////////////////////////////

#include "nmea/nmea_message.h"

#ifndef MSG_CFG_H
#define MSG_CFG_H

class MsgCFG : public NmeaMessage
{
public:
    MsgCFG();
    MsgCFG(int systemID, int mode, int wTrackPowLev, int wTrackPulseLen, int wTrackRangeOffset,
           QString formats, int bTrackPowLev, int bTrackPulseLen, int bTrackRangeOffset, int pingMode);

    int systemID;
    int mode;                                      // xx = MODE
    int wTrackPowLev;                              // x = Water track Power level 0-3
    int wTrackPulseLen;                            // x = Water track Pulse length 0-3 (1,2,4,8ms)
    int wTrackRangeOffset;                         // xx = Water track Range offset in x*0.5m (1-31) (0.5-16.5m)
    QString formats;                               // AAAA = Formats
    int bTrackPowLev;                              // x = Bottomr track Power level 0-3
    int bTrackPulseLen;                            // x = Bottom track Pulse length 0-3 (1,2,4,8ms)
    int bTrackRangeOffset;                         // xx = Bottom track Range offset in x*0.5m (1-31) (0.5-16.5m)
    int pingMode;                                  // x = Ping mode


    static const unsigned long CFGhash = 4408903;

    bool setParams(QStringList m_message_parameters);

    virtual QString getMsgBuffer();

    MsgCFG * clone() {return new MsgCFG(*this);}
};

#endif
