#include "flprogDisplayScreen.h"

void FLProgAbstractDisplayScreen::setFieldsCount(uint8_t fieldsCounts)
{
    _fieldsCounts = fieldsCounts;
    if (_fieldsCounts != 0)
    {
        _fields = new FLProgAbstractField *[_fieldsCounts];
    }
}

void FLProgAbstractDisplayScreen::setIsNeedShowAllFields()
{
    if (_fieldsCounts == 0)
    {
        return;
    }
    for (uint8_t i = 0; i < _fieldsCounts; i++)
    {
        if (_fields[i] != 0)
        {
            _fields[i]->setIsNeedShow();
        }
    }
}

void FLProgAbstractDisplayScreen::addField(FLProgAbstractField *field)
{
    if (_fieldsCounts == 0)
    {
        return;
    }
    for (uint8_t i = 0; i < _fieldsCounts; i++)
    {
        if (_fields[i] != 0)
        {
            _fields[i] = field;
            return;
        }
    }
}

FLProgTextDisplayScreen::FLProgTextDisplayScreen(uint8_t fieldsCounts)
{
    setFieldsCount(fieldsCounts);
}

FLProgAbstractField *FLProgTextDisplayScreen::getShowField()
{
    if (_fieldsCounts == 0)
    {
        return 0;
    }
    for (uint8_t i = 0; i < _fieldsCounts; i++)
    {
        if (_fields[i] != 0)
        {
            if (_fields[i]->isNeedShow())
            {
                _showField = _fields[i];
                _showField->resetIsNeedShow();
                _showField->blockShow();
                return _showField;
            }
        }
    }
    if (_showField == 0)
    {
        return _showField;
    }
    for (uint8_t i = 0; i < _fieldsCounts; i++)
    {
        if (_fields[i] != 0)
        {
            _fields[i]->unBlockShow();
        }
    }
    _showField = 0;
    return _showField;
}
