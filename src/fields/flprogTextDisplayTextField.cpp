#include "flprogTextDisplayTextField.h"

FLProgTextDisplayTextField::FLProgTextDisplayTextField(uint8_t row, uint8_t col, String text)
{
    _row = row;
    _col = col;
    _text = text;
    _length = _text.length();
}

String FLProgTextDisplayTextField::bufferString()
{
    _showTime = millis();
    return _text;
}

bool FLProgTextDisplayTextField::checkIsNeedShow()
{
    if (RT_HW_Base.getIsTimerMs(_showTime, _showPeriod))
    {
        _isNeedShow = true;
        return _isNeedShow;
    }
    return false;
}