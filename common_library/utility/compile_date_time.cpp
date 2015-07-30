#include "compile_date_time.h"
#include <QStringList>
#include <QDateTime>

QString CompileDateTime::getCompileTimestampAsNumber()
{
    QString buildDateTime = QString(__DATE__) + QString(__TIME__);
    QDateTime date = QDateTime::fromString(buildDateTime.simplified(), "MMM d yyyyhh:mm:ss");

    return date.toString("yyMMddHHmmss");
}

QString CompileDateTime::getCompileDateAsNumber()
{
    QString buildDateTime = QString(__DATE__) + QString(__TIME__);
    QDateTime date = QDateTime::fromString(buildDateTime.simplified(), "MMM d yyyyhh:mm:ss");

    return date.toString("yyMMdd");
}
