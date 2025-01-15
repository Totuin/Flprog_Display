#include "flprogAbstractField.h"

bool FLProgAbstractField::isNeedShow()
{
    if (_isBlockShow)
    {
        return false;
    }
    if (_isNeedShow)
    {
        return true;
    }
    return checkIsNeedShow();
}
