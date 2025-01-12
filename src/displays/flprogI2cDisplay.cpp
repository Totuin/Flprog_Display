#include "flprogI2cDisplay.h"

FLProgI2c8bitDisplay::FLProgI2c8bitDisplay(uint8_t address, uint8_t busNumber, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setBusNumber(busNumber);
    setAddress(address);
}

void FLProgI2c8bitDisplay::setBusNumber(uint8_t busNumber)
{
    if (busNumber == _device.bus)
    {
        return;
    }
    _device.bus = busNumber;
}

void FLProgI2c8bitDisplay::setAddress(uint8_t address)
{
    if (address == _device.addr)
    {
        return;
    }
    _device.addr = address;
}

void FLProgI2c8bitDisplay::setSpeed(uint8_t speed)
{
    if (_device.speed == speed)
    {
        return;
    }
    _device.speed = speed;
}

void FLProgI2c8bitDisplay::pool()
{
    setFlags();
    if (_device.custom == 0)
    {
        _device.custom = 1;
    }
    if ((_status == FLPROG_NOT_REDY_STATUS) || (_status == FLPROG_WAIT_I2C_INIT))
    {
        RT_HW_Base.i2cInitDevice(_device);
        _errorCode = _device.codeErr;
        if (_status == FLPROG_NOT_REDY_STATUS)
        {
            _status = FLPROG_WAIT_I2C_INIT;
            return;
        }
        if (_device.link)
        {
            _status = FLPROG_WAIT_I2C_FIND_ADDRESS;
        }
        else
        {
            return;
        }
    }
    if (_status == FLPROG_WAIT_I2C_FIND_ADDRESS)
    {
        if (checkAddress())
        {
            clearDisplay();
            _status = FLPROG_READY_STATUS;
        }
        else
        {
            return;
        }
    }
    if (_status == FLPROG_READY_STATUS)
    {
        setEnableScreen();
        if (_enableScreen == 0)
        {
            return;
        }
    }
    if (_status == FLPROG_WAIT_SEND_DISPLAY_BUFFER)
    {
        sendBuffer();
        return;
    }
    showScreen();
}

bool FLProgI2c8bitDisplay::checkAddress()
{
    if ((!_oKCount) || (!_errorCount))
    {
        if (!(RT_HW_Base.getIsTimerMs(_delayStartTime, _delayValue)))
        {
            return false;
        }
    }
    RT_HW_Base.i2cFindAddr(_device);
    _errorCode = _device.codeErr;
    _delayStartTime = millis();
    if (_errorCode)
    {
        _oKCount = 0;
        if (_errorCount > 3)
        {
            _delayValue = 2000;
            return false;
        }
        else
        {
            _delayValue = 100 + (250 * _errorCount);
            _errorCount++;
            return false;
        }
    }
    _errorCount = 0;
    if (_oKCount > 2)
    {
        _oKCount = 0;
        return true;
    }
    _delayValue = 20;
    _oKCount++;
    return false;
}

void FLProgI2c8bitDisplay::sendToInterface(uint8_t *sendArray, uint8_t type)
{
    if (type != FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND)
    {
        RT_HW_Base.i2cWriteArr(_device, &sendArray[0], 4);
    }
    else
    {
        RT_HW_Base.i2cWriteArr(_device, &sendArray[2], 2);
    }
    _errorCode = _device.codeErr;
    if (!_device.link)
    {
        _status = FLPROG_NOT_REDY_STATUS;
    }
}

void FLProgI2c8bitDisplay::clearDisplay()
{
    uint8_t sendArray[4] = {0, 0, 0, 0};
    privatePrepareSendArray(sendArray, 1, 0b00000001, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    sendToInterface(sendArray, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
    delayMicroseconds(40);
    if (chipCount() > 1)
    {
        privatePrepareSendArray(sendArray, 2, 0b00000001, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
        sendToInterface(sendArray, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND);
        delayMicroseconds(40);
    }
}

FLProgI2c16bitDisplay::FLProgI2c16bitDisplay(uint8_t address, uint8_t busNumber, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setBusNumber(busNumber);
    setAddress(address);
}