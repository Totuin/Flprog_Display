#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"



class FLProgAbstractField
{
public:
    void setIsNeedShow() { _isNeedShow = true; };
    void resetIsNeedShow() { _isNeedShow = false; };
    bool isNeedShow();
    void blockShow() { _isBlockShow = true; };
    void unBlockShow() { _isBlockShow = false; };

    virtual uint8_t row() { return 0; };
    virtual uint8_t col() { return 0; };
    virtual uint8_t length() { return 0; };
    virtual String bufferString() { return ""; };

protected:
    virtual bool checkIsNeedShow() { return true; };
    bool _isNeedShow = true;
    bool _isBlockShow = false;
};

class FLProgAbstractTextDisplayField : public FLProgAbstractField
{
public:
    virtual uint8_t row() { return _row; };
    virtual uint8_t col() { return _col; };
    virtual uint8_t length() { return _length; };
    virtual String bufferString() { return ""; };

protected:
    uint8_t _row = 1;
    uint8_t _col = 1;
    uint8_t _length = 0;
};

#include "flprogTextDisplayTextField.h"