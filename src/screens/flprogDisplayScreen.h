#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "../fields/flprogAbstractField.h"

class FLProgAbstractDisplayScreen
{
public:
    void setFieldsCount(uint8_t fieldsCounts);

    bool enable() { return _enable; };
    void enable(bool value) { _enable = value; };
    void setEnable() { _enable = true; };
    void resetEnable() { _enable = false; };
    void addField(FLProgAbstractField *field);

    void setIsNeedShowAllFields();
    FLProgTextFieldSendBuffer *getTextBuffer() { return 0; };

protected:
    FLProgAbstractField **_fields;
    bool _enable = false;
    uint8_t _fieldsCounts = 0;
};

class FLProgTextDisplayScreen : public FLProgAbstractDisplayScreen
{
public:
    FLProgTextDisplayScreen(uint8_t fieldsCounts);
    FLProgTextDisplayScreen() {};
    FLProgTextFieldSendBuffer *getTextBuffer();

protected:
    FLProgTextFieldSendBuffer *_tempBuffer = 0;
};
