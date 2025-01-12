#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"

struct FLProgTextFieldSendBuffer
{
    String buffer = "";
    uint8_t length;
    uint8_t row;
    uint8_t col;
    uint8_t pointCursor;
};

class FLProgAbstractField
{
public:
    void setIsNeedShow() { _isNeedShow = true; };
    void resetIsNeedShow() { _isNeedShow = false; };
    bool isNeedShow() ;
    void blockShow() { _isBlockShow = true; };
    void unBlockShow() { _isBlockShow = false; };
    
    virtual FLProgTextFieldSendBuffer *getTextBuffer() { return 0; };

protected:
    virtual bool checkIsNeedShow() { return true; };
    bool _isNeedShow = true;
    bool _isBlockShow = false;
};

class FLProgAbstractTextField : public FLProgAbstractField
{
public:
    virtual FLProgTextFieldSendBuffer *getTextBuffer();

protected:
    virtual String bufferString() { return "C"; };
    uint8_t _row = 1;
    uint8_t _col = 1;
    uint8_t _length = 1;
};