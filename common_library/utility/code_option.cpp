#include "code_option.h"

#define MAX_OPTIONS_COUNT 50

////////////////////////////////////////////////////////////////////////
// "ID":      serial No. of this unit
// "codenum": user entered code
////////////////////////////////////////////////////////////////////////
bool CodeOption::validateOnePercentAccuracyOption(quint32 id, quint32 code_number)
{
    return validate(id, code_number, OPTION_ONE_PERCENT);
}

////////////////////////////////////////////////////////////////////////
// "ID":      serial No. of this unit
// "codenum": user entered code
////////////////////////////////////////////////////////////////////////
bool CodeOption::validateSyncOption(quint32 id, quint32 code_number)
{
    return validate(id, code_number, OPTION_SYNC);
}


/*  Description:  New Security algorithm is implemented from version 1.13.
                  Calculates code number (1-50) based on codenum
  Inputs:       ID - serial number and
                 codenum - number generated by "encrypt" function
  Outputs:      option value (0-49) og Negative (-1) value if illegal value*/
bool CodeOption::validate(quint32 id, quint32 code_number, quint8 option)
{
    quint32 result = encryption(id, option);

    if (result == code_number)
        return true;

    return false;
}

quint32 CodeOption::encryption(quint32 id, quint8 option)
/*  Function:     encryption
*   Date:         August 2012
*   Description:  New Security algorithm is implemented from version 1.13.
                  Calculates code number (0-49) based on codenum
*   Inputs:       ID - serial number and
*                 option - number from 0 to 49 (50(MAX_OPTIONS_COUNT) different options)
*   Outputs:      Security word
*   Uses:
*   Changes:
*/
{
  quint32 ret;

  quint32 key[] =  {12345, 72333, 21212, 43432, 12234, 35321, 78567, 56542, 76432, 26212,
                 32115, 33723, 25992, 11466, 84657, 52434, 97454, 37543, 67354, 83567,
                 67413, 72413, 75411, 67134, 96595, 69841, 95547, 87281, 13578, 98453,
                 74276, 87663, 12325, 24578, 87542, 75643, 76894, 42677, 92378, 15899,
                 65665, 76877, 37658, 43677, 26575, 16576, 67933, 24828, 48484, 30223};

  ret = (id ^(key[option]) ^key[(id%MAX_OPTIONS_COUNT)]);
  while (ret > 99999)
    ret %= 99999;  // limit to 5 digits

  return ret;
}