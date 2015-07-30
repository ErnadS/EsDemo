#include "Crc8.h"

// Return CRC8 as hex number (2 chars)
QString CRC8::calculateChecksum(char *start, int nLength)
{
    quint8 checksum = 0;
    QString crcHex;
    int nPos = 0;

    while (nPos < nLength)
    {
        checksum ^= *start;

        start++;
        nPos ++;
    }

    crcHex = QString::number( checksum, 16 );
    crcHex = crcHex.toUpper();

    if (crcHex.length() < 2)
        crcHex.prepend('0');

    return crcHex;
}

////////////////////////////////////////////////////////////////////////////
// Argument examples:
////////////////////////////////////////////////////////////////////////////
// "VDWMT,12.9,,1"           // NMEA message (without "$" and "*")
// "s:VM002,d:II0988,n:023"  // UDP header
////////////////////////////////////////////////////////////////////////////
QString CRC8::calculateChecksum(QString msg)
{
    return calculateChecksum(msg.toLatin1().data(), msg.length());
}


/////////////////////////////////////////////////////////////////////////////
// expected format is without "$" on the start.
// e.g.:
// GPGGA,10.23,0,2,1*A8         // return "CRC_8_OK" or "CRC_8_ERROR"
// GPGGA,10.23,0,2,1            // without "CRC" => return "NO_CRC"
// GPGGA,10.23,*2,1*A8          // return "CRC_8_FORMAT_ERROR"
/////////////////////////////////////////////////////////////////////////////
int CRC8::validateCrc(QString msg)
{
    int nIndex;

    nIndex = msg.indexOf("*");
    if (nIndex < 0)
        return NO_CRC;

    if (nIndex !=  msg.length() - 3)  // found '*' on unexpected possition. It should not be '*' inside messages body
        return CRC_8_FORMAT_ERROR;

    QString  msgCRC;
    msgCRC = msg.mid(msg.length() - 2);

    QString caclulatedCRC = calculateChecksum(msg.toLatin1().data(), msg.length() - 3);
    if (QString::compare(msgCRC, caclulatedCRC, Qt::CaseInsensitive) != 0)
        return CRC_8_ERROR;
    else
        return CRC_8_OK;
}
