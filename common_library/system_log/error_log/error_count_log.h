#ifndef ERROR_COUNT_LOG_H
#define ERROR_COUNT_LOG_H

#include <QObject>
#include "configuration/serialization_controller.h"

class ErrorCountLog : public QObject
{
    Q_OBJECT

    unsigned udpCrcError;                           // ErrorID  70
    unsigned linesWithTagCrcError;                  // ErrorID  71
    unsigned linesWithTagSyntaxError;               // ErrorID  72
    unsigned linesWithTagFramingError;              // ErrorID  73
    unsigned incorrectMsgLength;                    // ErrorID  74
    unsigned udpOverflowReasem;                     // ErrorID  75
    unsigned msgFormatError;                        // ErrorID  76
    unsigned badSigQuality;                         // ErrorID  77
    unsigned rejectedMsgs;                          // ErrorID  78

    unsigned latestErrorCode;                       // ErrorID of the last error to occur
/*
    unsigned udpCrcErrorID;                           // ErrorID  70
    unsigned linesWithTagCrcErrorID;                  // ErrorID  71
    unsigned linesWithTagSyntaxErrorID;               // ErrorID  72
    unsigned linesWithTagFramingErrorID;              // ErrorID  73
    unsigned incorrectMsgLengthID;                    // ErrorID  74
    unsigned udpOverflowReasemID;                     // ErrorID  75
    unsigned msgFormatErrorID;                        // ErrorID  76
    unsigned badSigQualityID;                         // ErrorID  77
    unsigned rejectedMsgsID;                          // ErrorID  78
*/
    Q_PROPERTY(unsigned udpCrcError READ getUdpCrcError WRITE setUdpCrcError)
    Q_PROPERTY(unsigned linesWithTagCrcError READ getLinesWithTagCrcError WRITE setLinesWithTagCrcError)
    Q_PROPERTY(unsigned linesWithTagSyntaxError READ getLinesWithTagSyntaxError WRITE setLinesWithTagSyntaxError)
    Q_PROPERTY(unsigned linesWithTagFramingError READ getLinesWithTagFramingError WRITE setLinesWithTagFramingError)
    Q_PROPERTY(unsigned incorrectMsgLength READ getIncorrectMsgLength WRITE setIncorrectMsgLength)
    Q_PROPERTY(unsigned udpOverflowReasem READ getUdpOverflowReasem WRITE setUdpOverflowReasem)
    Q_PROPERTY(unsigned msgFormatError READ getMsgFormatError WRITE setMsgFormatError)
    Q_PROPERTY(unsigned badSigQuality READ getBadSigQuality WRITE setBadSigQuality)
    Q_PROPERTY(unsigned rejectedMsgs READ getRejectedMsgs WRITE setRejectedMsgs)

    Q_PROPERTY(unsigned latestErrorCode READ getLatestErrorCode WRITE setLatestErrorCode)


/*
    Q_PROPERTY(unsigned udpCrcErrorID READ getUdpCrcErrorID WRITE setUdpCrcErrorID)
    Q_PROPERTY(unsigned linesWithTagCrcErrorID READ getLinesWithTagCrcErrorID WRITE setLinesWithTagCrcErrorID)
    Q_PROPERTY(unsigned linesWithTagSyntaxErrorID READ getLinesWithTagSyntaxErrorID WRITE setLinesWithTagSyntaxErrorID)
    Q_PROPERTY(unsigned linesWithTagFramingErrorID READ getLinesWithTagFramingErrorID WRITE setLinesWithTagFramingErrorID)
    Q_PROPERTY(unsigned incorrectMsgLengthID READ getIncorrectMsgLengthID WRITE setIncorrectMsgLengthID)
    Q_PROPERTY(unsigned udpOverflowReasemID READ getUdpOverflowReasemID WRITE setUdpOverflowReasemID)
    Q_PROPERTY(unsigned msgFormatErrorID READ getMsgFormatErrorID WRITE setMsgFormatErrorID)
    Q_PROPERTY(unsigned badSigQualityID READ getBadSigQualityID WRITE setBadSigQualityID)
    Q_PROPERTY(unsigned rejectedMsgsID READ getRejectedMsgsID WRITE setRejectedMsgsID)
*/
public:
    explicit ErrorCountLog(QObject *parent = 0);

    unsigned getUdpCrcError() const;
    void setUdpCrcError(const unsigned &value);

    unsigned getLinesWithTagCrcError() const;
    void setLinesWithTagCrcError(const unsigned &value);

    unsigned getLinesWithTagSyntaxError() const;
    void setLinesWithTagSyntaxError(const unsigned &value);

    unsigned getLinesWithTagFramingError() const;
    void setLinesWithTagFramingError(const unsigned &value);

    unsigned getIncorrectMsgLength() const;
    void setIncorrectMsgLength(const unsigned &value);

    unsigned getUdpOverflowReasem() const;
    void setUdpOverflowReasem(const unsigned &value);

    unsigned getMsgFormatError() const;
    void setMsgFormatError(const unsigned &value);

    unsigned getBadSigQuality() const;
    void setBadSigQuality(const unsigned &value);

    unsigned getRejectedMsgs() const;
    void setRejectedMsgs(const unsigned &value);
/*
    unsigned getUdpCrcErrorID() const;
    void setUdpCrcErrorID(const unsigned &value);

    unsigned getLinesWithTagCrcErrorID() const;
    void setLinesWithTagCrcErrorID(const unsigned &value);

    unsigned getLinesWithTagSyntaxErrorID() const;
    void setLinesWithTagSyntaxErrorID(const unsigned &value);

    unsigned getLinesWithTagFramingErrorID() const;
    void setLinesWithTagFramingErrorID(const unsigned &value);

    unsigned getIncorrectMsgLengthID() const;
    void setIncorrectMsgLengthID(const unsigned &value);

    unsigned getMsgFormatErrorID() const;
    void setMsgFormatErrorID(const unsigned &value);

    unsigned getBadSigQualityID() const;
    void setBadSigQualityID(const unsigned &value);

    unsigned getRejectedMsgsID() const;
    void setRejectedMsgsID(const unsigned &value);

    unsigned getUdpOverflowReasemID() const;
    void setUdpOverflowReasemID(const unsigned &value);
*/
    unsigned getLatestErrorCode() const;
    void setLatestErrorCode(const unsigned &value);
};

#endif
