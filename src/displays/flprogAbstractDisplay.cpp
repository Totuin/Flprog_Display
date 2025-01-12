#include "flprogAbstractDisplay.h"

void FLProgAbstractTexttDisplay::addScreen(FLProgTextDisplayScreen *screen)
{
    uint8_t index = freeScreenIndex();
    if (index == 255)
    {
        return;
    }
    _screens[index] = screen;
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

void FLProgAbstractTexttDisplay::setEnableScreen()
{
    Serial.println("setEnableScreenFunction");
    if (_screensCount == 0)
    {
        return;
    }
    for (uint8_t i = 0; i < _screensCount; i++)
    {
        if (_screens[i] != 0)
        {
            if (_screens[i]->enable())
            {
                if (_enableScreen == _screens[i])
                {
                    return;
                }
                clearDisplay();
                _enableScreen = _screens[i];
                _enableScreen->setIsNeedShowAllFields();
                return;
            }
        }
    }
    if (_enableScreen != 0)
    {
        clearDisplay();
        _enableScreen = 0;
    }
    return;
}

uint8_t FLProgAbstractTexttDisplay::freeScreenIndex()
{
    if (_screensCount == 0)
    {
        return 255;
    }
    for (uint8_t i = 0; i < _screensCount; i++)
    {
        if (_screens[i] == 0)
        {

            return i;
        }
    }
    return 255;
}

void FLProgAbstractTexttDisplay::setScreensCount(uint8_t screensCount)
{
    _screensCount = screensCount;
    if (_screensCount != 0)
    {
        _screens = new FLProgTextDisplayScreen *[_screensCount];
    }
}

void FLProgAbstractTexttDisplay::createScreen(uint8_t fieldsCounts)
{
    uint8_t index = freeScreenIndex();
    if (index == 255)
    {
        return;
    }
    _screens[index] = new FLProgTextDisplayScreen(fieldsCounts);
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

void FLProgAbstractTexttDisplay::showScreen()
{
    setEnableScreen();
    if (_enableScreen == 0)
    {
        _buffer = 0;
        return;
    }
    _buffer = _enableScreen->getTextBuffer();
    if (_buffer == 0)
    {
        return;
    }
    setCursorPointToBuffer();
    _status = FLPROG_WAIT_SEND_DISPLAY_BUFFER;
    sendBuffer();
}

void FLProgAbstractTexttDisplay::setCursorPointToBuffer()
{
    if (_buffer == 0)
    {
        return;
    }
    _buffer->pointCursor = ((((_buffer->col) - 1) + rowIffset()) | 0x80);
}

uint8_t FLProgAbstractTexttDisplay::rowIffset()
{
    if (_buffer == 0)
    {
        return 0;
    }
    if (_buffer->row == 1)
    {
        return 0x00;
    }
    if (_buffer->row == 2)
    {
        return 0x40;
    }
    if (_buffer->row == 3)
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

void FLProgAbstractTexttDisplay::sendBuffer()
{
    if (_sendBufferStep == FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP)
    {
        setCursor();
        if (_status == FLPROG_WAIT_SEND_DISPLAY_BUFFER)
        {
            _delayValue = 37;
            _delayStartTime = micros();
            _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_WAIT_SET_CURSOR_STEP;
            return;
        }
        else
        {
            _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
        }
    }
    if (_sendBufferStep == FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP)
    {
        if (!RT_HW_Base.getIsTimerUs(_delayStartTime, _delayValue))
        {
            return;
        }
    }
    _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_SEND_DATA_STEP;
    sendBufferString();
}

void FLProgAbstractTexttDisplay::setCursor()
{
    uint8_t sendArray[4];
    prepareSendArray(sendArray, _buffer->pointCursor, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    sendToInterface(sendArray, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
}

void FLProgAbstractTexttDisplay::sendBufferString()
{
    uint8_t sendArray[4];
    uint8_t bufferByte;
    uint8_t bufferLength = _buffer->buffer.length();
    for (uint8_t i = 0; i < _buffer->length; i++)
    {
        if (bufferLength >= (i + 1))
        {
            bufferByte = (uint8_t)_buffer->buffer[i];
            sendArray[0] = 0;
            sendArray[1] = 0;
            sendArray[2] = 0;
            sendArray[3] = 0;
            prepareSendArray(sendArray, bufferByte, FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND);
            sendToInterface(sendArray, FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND);
            if (!(_status == FLPROG_WAIT_SEND_DISPLAY_BUFFER))
            {
                _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
                return;
            }
        }
    }
    _status = FLPROG_READY_STATUS;
    _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
}

void FLProgAbstractTexttDisplay::prepareSendArray(uint8_t *sendArray, uint8_t value, uint8_t type)
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
    if (_buffer->row > 2)
    {
        chipControlBit = bitRW();
    }
    else
    {
        chipControlBit = bitE();
    }
    if (type != FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND)
    {
        bitWrite(sendByte, bitRS(), cmdSend);
        bitWrite(sendByte, bitOn(), lightOn);
        bitSet(sendByte, chipControlBit);
        sendArray[0] = sendByte;
        bitClear(sendByte, chipControlBit);
        sendArray[1] = sendByte;
    }
    sendByte = value << 4;
    bitWrite(sendByte, bitRS(), cmdSend);
    bitWrite(sendByte, bitOn(), lightOn);
    bitSet(sendByte, chipControlBit);
    sendArray[2] = sendByte;
    bitClear(sendByte, chipControlBit);
    sendArray[4] = sendByte;
}

void FLProgAbstractTexttDisplay::sendToInterface(uint8_t *sendArray, uint8_t type)
{
    (void)sendArray;
    (void)type;
}