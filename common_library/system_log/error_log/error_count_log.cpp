#include "error_count_log.h"

unsigned ErrorCountLog::getUdpCrcError() const
{
    return udpCrcError;
}

void ErrorCountLog::setUdpCrcError(const unsigned &value)
{
    udpCrcError = value;
}

unsigned ErrorCountLog::getLinesWithTagCrcError() const
{
    return linesWithTagCrcError;
}

void ErrorCountLog::setLinesWithTagCrcError(const unsigned &value)
{
    linesWithTagCrcError = value;
}

unsigned ErrorCountLog::getLinesWithTagSyntaxError() const
{
    return linesWithTagSyntaxError;
}

void ErrorCountLog::setLinesWithTagSyntaxError(const unsigned &value)
{
    linesWithTagSyntaxError = value;
}

unsigned ErrorCountLog::getLinesWithTagFramingError() const
{
    return linesWithTagFramingError;
}

void ErrorCountLog::setLinesWithTagFramingError(const unsigned &value)
{
    linesWithTagFramingError = value;
}

unsigned ErrorCountLog::getIncorrectMsgLength() const
{
    return incorrectMsgLength;
}

void ErrorCountLog::setIncorrectMsgLength(const unsigned &value)
{
    incorrectMsgLength = value;
}

unsigned ErrorCountLog::getUdpOverflowReasem() const
{
    return udpOverflowReasem;
}

void ErrorCountLog::setUdpOverflowReasem(const unsigned &value)
{
    udpOverflowReasem = value;
}

unsigned ErrorCountLog::getMsgFormatError() const
{
    return msgFormatError;
}

void ErrorCountLog::setMsgFormatError(const unsigned &value)
{
    msgFormatError = value;
}

unsigned ErrorCountLog::getBadSigQuality() const
{
    return badSigQuality;
}

void ErrorCountLog::setBadSigQuality(const unsigned &value)
{
    badSigQuality = value;
}

unsigned ErrorCountLog::getRejectedMsgs() const
{
    return rejectedMsgs;
}

void ErrorCountLog::setRejectedMsgs(const unsigned &value)
{
    rejectedMsgs = value;
}

/*
unsigned ErrorCountLog::getUdpOverflowReasemID() const
{
    return udpOverflowReasemID;
}

void ErrorCountLog::setUdpOverflowReasemID(const unsigned &value)
{
    udpOverflowReasemID = value;
}
unsigned ErrorCountLog::getUdpCrcErrorID() const
{
    return udpCrcErrorID;
}

void ErrorCountLog::setUdpCrcErrorID(const unsigned &value)
{
    udpCrcErrorID = value;
}

unsigned ErrorCountLog::getLinesWithTagCrcErrorID() const
{
    return linesWithTagCrcErrorID;
}

void ErrorCountLog::setLinesWithTagCrcErrorID(const unsigned &value)
{
    linesWithTagCrcErrorID = value;
}

unsigned ErrorCountLog::getLinesWithTagSyntaxErrorID() const
{
    return linesWithTagSyntaxErrorID;
}

void ErrorCountLog::setLinesWithTagSyntaxErrorID(const unsigned &value)
{
    linesWithTagSyntaxErrorID = value;
}

unsigned ErrorCountLog::getLinesWithTagFramingErrorID() const
{
    return linesWithTagFramingErrorID;
}

void ErrorCountLog::setLinesWithTagFramingErrorID(const unsigned &value)
{
    linesWithTagFramingErrorID = value;
}

unsigned ErrorCountLog::getIncorrectMsgLengthID() const
{
    return incorrectMsgLengthID;
}

void ErrorCountLog::setIncorrectMsgLengthID(const unsigned &value)
{
    incorrectMsgLengthID = value;
}

unsigned ErrorCountLog::getMsgFormatErrorID() const
{
    return msgFormatErrorID;
}

void ErrorCountLog::setMsgFormatErrorID(const unsigned &value)
{
    msgFormatErrorID = value;
}

unsigned ErrorCountLog::getBadSigQualityID() const
{
    return badSigQualityID;
}

void ErrorCountLog::setBadSigQualityID(const unsigned &value)
{
    badSigQualityID = value;
}

unsigned ErrorCountLog::getRejectedMsgsID() const
{
    return rejectedMsgsID;
}

void ErrorCountLog::setRejectedMsgsID(const unsigned &value)
{
    rejectedMsgsID = value;
}
*/


unsigned ErrorCountLog::getLatestErrorCode() const
{
    return latestErrorCode;
}

void ErrorCountLog::setLatestErrorCode(const unsigned &value)
{
    latestErrorCode = value;
}
ErrorCountLog::ErrorCountLog(QObject *parent) :
    QObject(parent)
{
}
