#include "flprogDisplayScreen.h"

void FLProgTextDisplayScreen::setFieldsCount(uint8_t fieldsCounts)
{
    _fieldsCounts = fieldsCounts;
    if (_fieldsCounts != 0)
    {
        _fields = new FLProgAbstractTextDisplayField *[_fieldsCounts];
        for (uint8_t i = 0; i < fieldsCounts; i++)
        {
            _fields[i] = 0;
        }
    }
}

void FLProgTextDisplayScreen::setIsNeedShowAllFields()
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

void FLProgTextDisplayScreen::addField(FLProgAbstractTextDisplayField *field)
{
    if (_fieldsCounts == 0)
    {
        return;
    }
    for (uint8_t i = 0; i < _fieldsCounts; i++)
    {
        if (_fields[i] == 0)
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

FLProgAbstractTextDisplayField *FLProgTextDisplayScreen::getShowField()
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
                if (_showField != 0)
                {
                    _showField->resetIsNeedShow();
                    _showField->blockShow();
                    return _showField;
                }
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
