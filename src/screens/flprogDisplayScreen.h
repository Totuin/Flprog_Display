#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "../fields/flprogAbstractField.h"

class FLProgAbstractDisplayScreen
{
public:
        bool enable() { return _enable; };
    void enable(bool value) { _enable = value; };
    void setEnable() { _enable = true; };
    void resetEnable() { _enable = false; };

protected:
    bool _enable = false;
    uint8_t _fieldsCounts = 0;
};

class FLProgTextDisplayScreen : public FLProgAbstractDisplayScreen
{
public:
    FLProgTextDisplayScreen(uint8_t fieldsCounts);
    FLProgTextDisplayScreen() {};

    void setIsNeedShowAllFields();
    void setFieldsCount(uint8_t fieldsCounts);
    void addField(FLProgAbstractTextDisplayField *field);
    virtual FLProgAbstractTextDisplayField *getShowField();

protected:
    FLProgAbstractTextDisplayField **_fields;
    FLProgAbstractTextDisplayField *_showField = 0;
};
