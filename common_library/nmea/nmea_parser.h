#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "nmea_message.h"
#include "QStringList"
#include <limits>
#include "nmea_include.h"

class NmeaParser
{
public:
    NmeaParser();

    static NmeaMessage* parse(QString message);


    static unsigned long calculateMessageTypeHash(QString message_type);

    static float StringToFloat(QString string, bool* ok = 0);
    static float StringToInt(QString string, bool* ok = 0);

    static QString NumberToString(const int number);
    static QString NumberToString(const float number, const char format, int precision);

    static QString NumberToDisplayString(const int number);
    static QString NumberToDisplayString(const float number, const char format, int precision);

    static QString NumberToStringSigned(const int number);
    static QString NumberToStringSigned(const float number, const char format, const int precision);


    static unsigned long StringToULong(const QString string, bool* ok = 0);
    static QString UlongToString(const unsigned long number);
    static QString UlongToString_FixedLenght(const unsigned long number, const int NoOfLeadingZero);

    // LEADING ZERO
    static QString UintToString_FixedLength(const quint32 number, const int NoOfLeadingZero);
    static QString IntToString_FixedLength(const int number, const int NoOfLeadingZero);
    static QString FloatToString_FixedLength        (const float number, const int NoOfLeadingZero, const int precision);
    static QString FloatToString_FixedLength_Signed (const float number, const int NoOfLeadingZero, const int precision); // with sign (+ or -)


    static bool isNumberValidInt(const int value);
    static bool isNumberValidFloat(const float value);
    // Get number of digits of a number (overloaded to take optional parameter "minNum" in case of determining lenght of
    // values that should have leadin zeros when converted to string.

    template<typename T>
    static int getNumberOfDigits(const T& number, int minNum = 0);

    static int getNumberOfDecimals();

private:
    static NmeaMessage* createMessage(QString message_type, unsigned long msgHash, QStringList m_message_parameters);

};

template<typename T>
int NmeaParser::getNumberOfDigits(const T &number, int minNum)
{
    if(number == std::numeric_limits<T>::max())
        return 0;
    int digits = 1;
    T tempNum = number;
    T powTen = 10;
    if(tempNum < 0)
    {
        tempNum = tempNum * -1;
        digits++;
    }
    while(powTen < tempNum)
    {
        digits++;
        powTen*=10;
    }
    if(minNum > digits)
        return minNum;
    else
        return
                digits;
}

#endif
