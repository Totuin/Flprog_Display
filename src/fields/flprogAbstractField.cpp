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

FLProgTextFieldSendBuffer *FLProgAbstractTextDisplayField::getTextBuffer()
{
    FLProgTextFieldSendBuffer *temp = new FLProgTextFieldSendBuffer;
    temp->col = _col;
    temp->row = _row;
    temp->buffer = bufferString();
    temp->length = _length;
    return temp;
}
