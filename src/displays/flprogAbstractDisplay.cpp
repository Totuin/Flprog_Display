#include "flprogAbstractDisplay.h"

void FLProgAbstractTexttDisplay::addScreen(FLProgTextDisplayScreen *screen)
{
    if (_screensCount == 0)
    {
        return;
    }
    for (uint8_t i = 0; i < _screensCount; i++)
    {
        if (_screens[i] == 0)
        {
            _screens[i] = screen;
            return;
        }
    }
}

FLProgTextDisplayScreen *FLProgAbstractTexttDisplay::screenAt(uint8_t index)
{
    if (_screensCount == 0)
    {
        return 0;
    }
    if (index > (_screensCount - 1))
    {
        return 0;
    }
    return _screens[index];
}

bool FLProgAbstractTexttDisplay::setEnableScreen()
{
    if (_screensCount == 0)
    {
        return false;
    }
    for (uint8_t i = 0; i < _screensCount; i++)
    {
        if (_screens[i] != 0)
        {
            if (_screens[i]->enable())
            {
                if (_enableScreen == _screens[i])
                {
                    return true;
                }
                clearDisplay();
                _enableScreen = _screens[i];
                _enableScreen->setIsNeedShowAllFields();
                return true;
            }
        }
    }
    if (_enableScreen != 0)
    {
        clearDisplay();
        _enableScreen = 0;
    }
    return false;
}

void FLProgAbstractTexttDisplay::setScreensCount(uint8_t screensCount)
{
    _screensCount = screensCount;
    if (_screensCount != 0)
    {
        _screens = new FLProgTextDisplayScreen *[_screensCount];
        for (uint8_t i = 0; i < _screensCount; i++)
        {
            _screens[i] = 0;
        }
    }
}

void FLProgAbstractTexttDisplay::createScreen(uint8_t fieldsCounts)
{
    for (uint8_t i = 0; i < _screensCount; i++)
    {
        if (_screens[i] == 0)
        {
            _screens[i] = new FLProgTextDisplayScreen(fieldsCounts);
        }
    }
}
void FLProgAbstractTexttDisplay::createScreen(uint8_t fieldsCounts, uint8_t index)
{
    if (_screensCount == 0)
    {
        return;
    }
    if (index > (_screensCount - 1))
    {
        return;
    }
    _screens[index] = new FLProgTextDisplayScreen(fieldsCounts);
}

uint8_t FLProgAbstractTexttDisplay::chipCount()
{
    if (_rows < 4)
    {
        return 1;
    }
    if (_cols < 40)
    {
        return 1;
    }
    return 2;
}

void FLProgAbstractTexttDisplay::light(bool value)
{
    if (value == _lightOn)
    {
        return;
    }
    _lightOn = value;
    _isNeedUpdateLight = true;
}

void FLProgAbstractTexttDisplay::showScreen()
{
    if (!setEnableScreen())
    {
        if (_isNeedUpdateLight)
        {
            sendLight();
            _isNeedUpdateLight = false;
        }
        return;
    }
    if (_enableScreen == 0)
    {
        return;
    }
    FLProgAbstractField *showField = 0;
    showField = _enableScreen->getShowField();
    if (showField == 0)
    {
        if (_isNeedUpdateLight)
        {
            sendLight();
            _isNeedUpdateLight = false;
        }
        return;
    }
    _buffer.pointer = 0;
    _buffer.row = showField->row();
    _buffer.col = showField->col();
    _buffer.buffer = showField->bufferString();
    setCursorPointToBuffer();
    _isNeedUpdateLight = false;
    _status = FLPROG_WAIT_SEND_DISPLAY_BUFFER;
    _sendBufferStep == FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
}

void FLProgAbstractTexttDisplay::sendLight()
{
    clearSendArray();
    prepareSendArray(0, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    sendToInterface(FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
}

void FLProgAbstractTexttDisplay::setCursorPointToBuffer()
{
    _buffer.pointCursor = ((((_buffer.col) - 1) + rowIffset()) | 0x80);
}

uint8_t FLProgAbstractTexttDisplay::rowIffset()
{

    if (_buffer.row == 1)
    {
        return 0x00;
    }
    if (_buffer.row == 2)
    {
        return 0x40;
    }
    if (_buffer.row == 3)
    {
        if (_cols <= 8)
        {
            return 0x08;
        }
        if (_cols <= 16)
        {
            return 0x10;
        }
        if (_cols <= 20)
        {
            return 0x14;
        }
        if (_cols <= 24)
        {
            return 0x14;
        }
        return 0x00;
    }
    if (_cols <= 8)
    {
        return 0x48;
    }
    if (_cols <= 16)
    {
        return 0x50;
    }
    if (_cols <= 20)
    {
        return 0x54;
    }
    if (_cols <= 24)
    {
        return 0x54;
    }
    return 0x40;
}

bool FLProgAbstractTexttDisplay::sendBuffer()
{
    if (_sendBufferStep == FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP)
    {
        if (setCursor())
        {
            _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_SEND_DATA_STEP;
        }
        return false;
    }
    if (sendBufferString())
    {
        _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
        return true;
    }
    return false;
}

bool FLProgAbstractTexttDisplay::setCursor()
{
    uint8_t point = _buffer.pointCursor;
    clearSendArray();
    prepareSendArray(point, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    sendToInterface(FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    if (_status == FLPROG_NOT_REDY_STATUS)
    {
        _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
        return false;
    }
    delayMicroseconds(37);
    return true;
}

bool FLProgAbstractTexttDisplay::sendBufferString()
{
    uint8_t bufferByte;
    uint8_t bufferLength = _buffer.buffer.length();
    for (uint8_t i = 0; i < bufferLength; i++)
    {
        bufferByte = (uint8_t)_buffer.buffer[i];
        clearSendArray();
        prepareSendArray(bufferByte, FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND);
        sendToInterface(FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND);
        if (_status == FLPROG_NOT_REDY_STATUS)
        {
            _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
            return false;
        }
    }
    return true;
}

void FLProgAbstractTexttDisplay::prepareSendArray(uint8_t value, uint8_t type)
{

    if (_buffer.row > 2)
    {
        privatePrepareSendArray(2, value, type);
    }
    else
    {
        privatePrepareSendArray(1, value, type);
    }
}

void FLProgAbstractTexttDisplay::privatePrepareSendArray(uint8_t chip, uint8_t value, uint8_t type)
{
    uint8_t sendByte = value & 0xf0;
    uint8_t chipControlBit;
    uint8_t cmdSend;
    if (type == FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND)
    {
        cmdSend = 1;
    }
    else
    {
        cmdSend = 0;
    }
    if (chip == 1)
    {
        chipControlBit = bitE(); // 2
    }
    else
    {
        chipControlBit = bitRW(); // 1
    }
    if (type != FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND)
    {
        bitWrite(sendByte, bitRS(), cmdSend);  // 0
        bitWrite(sendByte, bitOn(), _lightOn); // 3
        bitSet(sendByte, chipControlBit);
        _sendArray[0] = sendByte;
        bitClear(sendByte, chipControlBit);
        _sendArray[1] = sendByte;
    }
    sendByte = value << 4;
    bitWrite(sendByte, bitRS(), cmdSend);  // 0
    bitWrite(sendByte, bitOn(), _lightOn); // 3
    bitSet(sendByte, chipControlBit);
    _sendArray[2] = sendByte;
    bitClear(sendByte, chipControlBit);
    _sendArray[3] = sendByte;
}

bool FLProgAbstractTexttDisplay::initDisplay()
{
    if (chipCount() == 1)
    {
        if (bitCount() == 4)
        {
            return initLcd4OneChip();
        }
        return initLcd8OneChip();
    }
    if (bitCount() == 4)
    {
        return initLcd4TwoChip();
    }
    return initLcd8TwoChip();
}

void FLProgAbstractTexttDisplay::clearSendArray()
{
    _sendArray[0] = 0;
    _sendArray[1] = 0;
    _sendArray[2] = 0;
    _sendArray[3] = 0;
}

bool FLProgAbstractTexttDisplay::initLcd4OneChip()
{
    if (_initDisplayStep == FLPROG_TEXT_DISPLAY_INIT_DISPLAY_START_STEP)
    {
        _delayValue = 50000;
        _delayStartTime = micros();
        _initDisplayStepIndex = 0;
        _initDisplayStep = FLPROG_TEXT_DISPLAY_INIT_DISPLAY_DELAY_STEP;
        return false;
    }
    if (_initDisplayStep == FLPROG_TEXT_DISPLAY_INIT_DISPLAY_DELAY_STEP)
    {
        if (RT_HW_Base.getIsTimerUs(_delayStartTime, _delayValue))
        {
            _initDisplayStep = FLPROG_TEXT_DISPLAY_INIT_DISPLAY_NEXT_CODE_STEP;
            return false;
        }
        return false;
    }
    if (_initDisplayStepIndex > 11)
    {
        _initDisplayStepIndex = 0;
        return true;
    }
    uint8_t var = pgm_read_byte(RT_HW_LCD44780_INIT_BUS4 + (_initDisplayStepIndex * 3));
    uint8_t code = pgm_read_byte(RT_HW_LCD44780_INIT_BUS4 + (_initDisplayStepIndex * 3 + 1));
    clearSendArray();
    privatePrepareSendArray(1, var, code);
    sendToInterface(code);
    if (_status == FLPROG_NOT_REDY_STATUS)
    {
        _initDisplayStep = FLPROG_TEXT_DISPLAY_INIT_DISPLAY_START_STEP;
        _initDisplayStepIndex = 0;
        return false;
    }
    _delayValue = pgm_read_byte(RT_HW_LCD44780_INIT_BUS4 + (_initDisplayStepIndex * 3 + 2)) * 100;
    _delayStartTime = micros();
    _initDisplayStep = FLPROG_TEXT_DISPLAY_INIT_DISPLAY_DELAY_STEP;
    _initDisplayStepIndex++;
    return false;
}

bool FLProgAbstractTexttDisplay::initLcd8OneChip()
{
    return true;
}

bool FLProgAbstractTexttDisplay::initLcd4TwoChip()
{
    return true;
}

bool FLProgAbstractTexttDisplay::initLcd8TwoChip()
{
    return true;
}