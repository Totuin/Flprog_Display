#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "flprogAbstractField.h"

class FLProgTextDisplayTextField : public FLProgAbstractTextDisplayField
{
public:
    FLProgTextDisplayTextField(uint8_t row, uint8_t col, String text);
    virtual String bufferString();

protected:
    virtual bool checkIsNeedShow();
    String _text = "";
    uint32_t _showTime;
    uint32_t _showPeriod = 2000;
};