#ifndef COMPILE_DATE_TIME_H
#define COMPILE_DATE_TIME_H

#include <QString>
#include <QList>

class CompileDateTime
{
public:
    static QString getCompileTimestampAsNumber();
    static QString getCompileDateAsNumber();
};

#endif
