#ifndef ERROR_COUNTER_H
#define ERROR_COUNTER_H

#include "error_count_log.h"

enum ErrorTypeEnum {
    ERR_TYPE_UDP_CRC                = 70,
    ERR_TYPE_TAG_CRC                = 71,
    ERR_TYPE_TAG_SINTAX             = 72,
    ERR_TYPE_TAG_FRAMING            = 73,
    ERR_TYPE_MSG_LENGTH             = 74,
    ERR_TYPE_UDP_OVERFL_REASEM      = 75,
    ERR_TYPE_NMEA_FORMAT            = 76,
    ERR_TYPE_SIG_QUALITY            = 77,
    ERR_TYPE_TOTAL_REJECTED         = 78
};

class ErrorCounter
{
    explicit ErrorCounter();

    ErrorCountLog countLog;

    void rejectedMsgsIncrease();
public:
/*
    unsigned udpCrcError;                           // ErrorID  70
    unsigned linesWithTagCrcError;                  // ErrorID  71
    unsigned linesWithTagSyntaxError;               // ErrorID  72
    unsigned linesWithTagFramingError;              // ErrorID  73
    unsigned incorrectMsgLength;                    // ErrorID  74
    unsigned udpOverflowReasem;                     // ErrorID  75
    unsigned msgFormatError;                        // ErrorID  76
    unsigned badSigQuality;                         // ErrorID  77
    unsigned rejectedMsgs;                          // ErrorID  78*/

    void udpCrcErrorIncrease();
    void linesWithTagCrcErrorIncrease();
    void linesWithTagSyntaxErrorIncrease();
    void linesWithTagFramingErrorIncrease();
    void incorrectMsgLengthIncrease();
    void udpOverflowReasemIncrease();
    void msgFormatErrorIncrease();
    void badSigQualityIncrease();

    unsigned getErrorCountByID(unsigned errorID) const;
    unsigned getErrorCountByIndex(int errorIndex) const;
    unsigned getErrorCountByName(QString errorName) const;
    unsigned getErrorIdByName(QString errorName) const;
    unsigned getErrorIdByIndex(int errorIndex) const;

    unsigned getLatestErrorCode() const;

    QList<unsigned> getListOfErrorCodes() const;
    QList<unsigned> getListOfErrorCounts() const;

    void setLatestErrorCode(const unsigned &value);

    void countLogReset();

    unsigned getUdpCrcError() const;
    unsigned getLinesWithTagCrcError() const;
    unsigned getLinesWithTagSyntaxError() const;
    unsigned getLinesWithTagFramingError() const;
    unsigned getIncorrectMsgLength() const;
    unsigned getUdpOverflowReasem() const;
    unsigned getMsgFormatError() const;
    unsigned getBadSigQuality() const;
    unsigned getRejectedMsgs() const;

    unsigned getUdpCrcErrorID() const;
    unsigned getLinesWithTagCrcErrorID() const;
    unsigned getLinesWithTagSyntaxErrorID() const;
    unsigned getLinesWithTagFramingErrorID() const;
    unsigned getIncorrectMsgLengthID() const;
    unsigned getUdpOverflowReasemID() const;
    unsigned getMsgFormatErrorID() const;
    unsigned getBadSigQualityID() const;
    unsigned getRejectedMsgsID() const;

    static ErrorCounter* getInstance();
    void readFromLogFile();
    void writeToLogFile();

signals:

public slots:

};

#endif
