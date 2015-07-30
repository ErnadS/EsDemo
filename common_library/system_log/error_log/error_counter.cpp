#include "error_counter.h"
#include <QDebug>

ErrorCounter* errorCounter; // singltone, must be static

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
ErrorCounter* ErrorCounter::getInstance()
{
    if (errorCounter == NULL)
        errorCounter = new ErrorCounter();

    return errorCounter;
}
ErrorCounter::ErrorCounter()
{
    readFromLogFile();
}

void ErrorCounter::rejectedMsgsIncrease()
{
    if(countLog.getRejectedMsgs() < 99)
        countLog.setRejectedMsgs(countLog.getRejectedMsgs() + 1);
    writeToLogFile();
}

void ErrorCounter::udpCrcErrorIncrease()
{
    setLatestErrorCode(ERR_TYPE_UDP_CRC);
    if(countLog.getUdpCrcError() < 99)
        countLog.setUdpCrcError(countLog.getUdpCrcError() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::linesWithTagCrcErrorIncrease()
{
    setLatestErrorCode(ERR_TYPE_TAG_CRC);
    if(countLog.getLinesWithTagCrcError() < 99)
        countLog.setLinesWithTagCrcError(countLog.getLinesWithTagCrcError() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::linesWithTagSyntaxErrorIncrease()
{
    setLatestErrorCode(ERR_TYPE_TAG_SINTAX);
    if(countLog.getLinesWithTagSyntaxError() < 99)
        countLog.setLinesWithTagSyntaxError(countLog.getLinesWithTagSyntaxError() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::linesWithTagFramingErrorIncrease()
{
    setLatestErrorCode(ERR_TYPE_TAG_FRAMING);
    if(countLog.getLinesWithTagFramingError() < 99)
        countLog.setLinesWithTagFramingError(countLog.getLinesWithTagFramingError() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::incorrectMsgLengthIncrease()
{
    setLatestErrorCode(ERR_TYPE_MSG_LENGTH);
    if(countLog.getIncorrectMsgLength() < 99)
        countLog.setIncorrectMsgLength(countLog.getIncorrectMsgLength() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::udpOverflowReasemIncrease()
{
    setLatestErrorCode(ERR_TYPE_UDP_OVERFL_REASEM);
    if(countLog.getUdpOverflowReasem() < 99)
        countLog.setUdpOverflowReasem(countLog.getUdpOverflowReasem() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::msgFormatErrorIncrease()
{
    setLatestErrorCode(ERR_TYPE_NMEA_FORMAT);
    if(countLog.getMsgFormatError() < 99)
        countLog.setMsgFormatError(countLog.getMsgFormatError() + 1);
    rejectedMsgsIncrease();
}

void ErrorCounter::badSigQualityIncrease()
{
    setLatestErrorCode(ERR_TYPE_SIG_QUALITY);
    if(countLog.getBadSigQuality() < 99)
        countLog.setBadSigQuality(countLog.getBadSigQuality() + 1);
    rejectedMsgsIncrease();
}
/*
ERR_TYPE_UDP_CRC                = 70,
ERR_TYPE_TAG_CRC                = 71,
ERR_TYPE_TAG_SINTAX             = 72,
ERR_TYPE_TAG_FRAMING            = 73,
ERR_TYPE_MSG_LENGTH             = 74,
ERR_TYPE_UDP_OVERFL_REASEM      = 75,
ERR_TYPE_NMEA_FORMAT            = 76,
ERR_TYPE_SIG_QUALITY            = 77,
ERR_TYPE_TOTAL_REJECTED         = 78
*/
unsigned ErrorCounter::getErrorCountByID(unsigned errorID) const
{
    switch (errorID) {
    case ERR_TYPE_UDP_CRC:
        return getUdpCrcError();

    case ERR_TYPE_TAG_CRC:
        return getLinesWithTagCrcError();

    case ERR_TYPE_TAG_SINTAX:
        return getLinesWithTagSyntaxError();

    case ERR_TYPE_TAG_FRAMING:
        return getLinesWithTagFramingError();

    case ERR_TYPE_MSG_LENGTH:
        return getIncorrectMsgLength();

    case ERR_TYPE_UDP_OVERFL_REASEM:
        return getUdpOverflowReasem();

    case ERR_TYPE_NMEA_FORMAT:
        return getMsgFormatError();

    case ERR_TYPE_SIG_QUALITY:
        return getBadSigQuality();

    case ERR_TYPE_TOTAL_REJECTED:
        return getRejectedMsgs();

    default:
        return 0;
    }

}

unsigned ErrorCounter::getErrorCountByIndex(int errorIndex) const
{
  return getErrorCountByID(errorIndex + 70);
}

unsigned ErrorCounter::getErrorCountByName(QString errorName) const
{
    if(errorName == "udpCrcError")
        return getUdpCrcError();

    if(errorName == "linesWithTagCrcError")
        return getLinesWithTagCrcError();

    if(errorName == "linesWithTagSyntaxError")
        return getLinesWithTagSyntaxError();

    if(errorName == "linesWithTagFramingError")
        return getLinesWithTagFramingError();

    if(errorName == "incorrectMsgLength")
        return getIncorrectMsgLength();

    if(errorName == "udpOverflowReasem")
        return getUdpOverflowReasem();

    if(errorName == "msgFormatError")
        return getMsgFormatError();

    if(errorName == "badSigQuality")
        return getBadSigQuality();

    if(errorName == "rejectedMsgs")
        return getRejectedMsgs();

    else
        return 0;
}

unsigned ErrorCounter::getErrorIdByName(QString errorName) const
{
    if(errorName == "udpCrcError")
        return getUdpCrcErrorID();

    if(errorName == "linesWithTagCrcError")
        return getLinesWithTagCrcErrorID();

    if(errorName == "linesWithTagSyntaxError")
        return getLinesWithTagSyntaxErrorID();

    if(errorName == "linesWithTagFramingError")
        return getLinesWithTagFramingErrorID();

    if(errorName == "incorrectMsgLength")
        return getIncorrectMsgLengthID();

    if(errorName == "udpOverflowReasem")
        return getUdpOverflowReasemID();

    if(errorName == "msgFormatError")
        return getMsgFormatErrorID();

    if(errorName == "badSigQuality")
        return getBadSigQualityID();

    if(errorName == "rejectedMsgs")
        return getRejectedMsgsID();

    else
        return 0;
}

unsigned ErrorCounter::getErrorIdByIndex(int errorIndex) const
{
    switch (errorIndex) {
    case 0:
        return getUdpCrcErrorID();

    case 1:
        return getLinesWithTagCrcErrorID();

    case 2:
        return getLinesWithTagSyntaxErrorID();

    case 3:
        return getLinesWithTagFramingErrorID();

    case 4:
        return getIncorrectMsgLengthID();

    case 5:
        return getUdpOverflowReasemID();

    case 6:
        return getMsgFormatErrorID();

    case 7:
        return getBadSigQualityID();

    case 8:
        return getRejectedMsgsID();

    default:
        return 0;
    }
}

unsigned ErrorCounter::getLatestErrorCode() const
{
    return countLog.getLatestErrorCode();
}

QList<unsigned> ErrorCounter::getListOfErrorCodes() const
{
    QList<unsigned> errorCodesList;

    for(int i = 0; i < 15; i++) {
        if (getErrorCountByIndex(i) > 0)
            errorCodesList.append(getErrorIdByIndex(i));
        else
            errorCodesList.append(0);
    }
      //  errorCodesList.append(getErrorIdByIndex(i));
    return errorCodesList;
}

QList<unsigned> ErrorCounter::getListOfErrorCounts() const
{
    QList<unsigned> errorCountsList;

    for(int i = 0; i < 15; i++)
        errorCountsList.append(getErrorCountByIndex(i));
    return errorCountsList;
}

void ErrorCounter::setLatestErrorCode(const unsigned &value)
{
    countLog.setLatestErrorCode(value);
}

void ErrorCounter::countLogReset()
{
    qDebug()<< "XXXXXXXXXX Error counter reset";
    countLog.setBadSigQuality(0);
    countLog.setIncorrectMsgLength(0);
    countLog.setLinesWithTagCrcError(0);
    countLog.setLinesWithTagFramingError(0);
    countLog.setLinesWithTagSyntaxError(0);
    countLog.setMsgFormatError(0);
    countLog.setRejectedMsgs(0);
    countLog.setUdpCrcError(0);
    countLog.setUdpOverflowReasem(0);
    countLog.setLatestErrorCode(0);
    writeToLogFile();
}

unsigned ErrorCounter::getUdpCrcError() const
{
    return countLog.getUdpCrcError();
}

unsigned ErrorCounter::getLinesWithTagCrcError() const
{
    return countLog.getLinesWithTagCrcError();
}

unsigned ErrorCounter::getLinesWithTagSyntaxError() const
{
    return countLog.getLinesWithTagSyntaxError();
}

unsigned ErrorCounter::getLinesWithTagFramingError() const
{
    return countLog.getLinesWithTagFramingError();
}

unsigned ErrorCounter::getIncorrectMsgLength() const
{
    return countLog.getIncorrectMsgLength();
}

unsigned ErrorCounter::getUdpOverflowReasem() const
{
    return countLog.getUdpOverflowReasem();
}

unsigned ErrorCounter::getMsgFormatError() const
{
    return countLog.getMsgFormatError();
}

unsigned ErrorCounter::getBadSigQuality() const
{
    return countLog.getBadSigQuality();
}

unsigned ErrorCounter::getRejectedMsgs() const
{
    return countLog.getBadSigQuality();
}

unsigned ErrorCounter::getUdpCrcErrorID() const
{
    return ERR_TYPE_UDP_CRC; //countLog.getUdpCrcErrorID();
}

unsigned ErrorCounter::getLinesWithTagCrcErrorID() const
{
    return ERR_TYPE_TAG_CRC; //countLog.getLinesWithTagCrcErrorID();
}

unsigned ErrorCounter::getLinesWithTagSyntaxErrorID() const
{
    return ERR_TYPE_TAG_SINTAX; //countLog.getLinesWithTagSyntaxErrorID();
}

unsigned ErrorCounter::getLinesWithTagFramingErrorID() const
{
    return ERR_TYPE_TAG_FRAMING; //countLog.getLinesWithTagFramingErrorID();
}

unsigned ErrorCounter::getIncorrectMsgLengthID() const
{
    return ERR_TYPE_MSG_LENGTH; //countLog.getIncorrectMsgLengthID();
}

unsigned ErrorCounter::getUdpOverflowReasemID() const
{
    return ERR_TYPE_UDP_OVERFL_REASEM; //countLog.getUdpOverflowReasemID();
}

unsigned ErrorCounter::getMsgFormatErrorID() const
{
    return ERR_TYPE_NMEA_FORMAT; //countLog.getMsgFormatErrorID();
}

unsigned ErrorCounter::getBadSigQualityID() const
{
    return ERR_TYPE_SIG_QUALITY; //countLog.getBadSigQualityID();
}

unsigned ErrorCounter::getRejectedMsgsID() const
{
    return ERR_TYPE_TOTAL_REJECTED; //countLog.getRejectedMsgsID();
}




// Serialization
void ErrorCounter::readFromLogFile()
{
    if (!SerializationController::Deserialize(countLog, "Error_count_log", "log_files/"))
       countLogReset();
}

void ErrorCounter::writeToLogFile()
{
    SerializationController::Serialize(countLog, "Error_count_log", "log_files/");
}

