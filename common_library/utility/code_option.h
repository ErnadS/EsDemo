#ifndef CODE_OPTION_H
#define CODE_OPTION_H

#include <QString>

class CodeOption
{
    static const quint32 OPTION_ONE_PERCENT{0};
    static const quint32 OPTION_SYNC{1};

public:
    static bool validateOnePercentAccuracyOption(quint32 id, quint32 code_number);
    static bool validateSyncOption(quint32 id, quint32 code_number);

    static quint32 encryption(quint32 id, quint8 option);

private:
    static bool validate(quint32 id, quint32 code_number, quint8 option);
};

#endif
