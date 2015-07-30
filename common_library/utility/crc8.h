#ifndef CRC8_H
#define CRC8_H

#include <QString>

#define CRC_8_OK                 0
#define NO_CRC                   1
#define CRC_8_ERROR             -1
#define CRC_8_FORMAT_ERROR      -2

class CRC8
{
public:
    static QString calculateChecksum(char* start, int nLength);
    static QString calculateChecksum(QString msg);
    static int validateCrc(QString msg);
};

#endif
