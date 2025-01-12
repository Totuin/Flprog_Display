#pragma once
#include "flprogAbstractDisplay.h"

class FLProgI2c8bitDisplay : public FLProgAbstractTexttDisplay
{
public:
    FLProgI2c8bitDisplay() {};
    FLProgI2c8bitDisplay(uint8_t address, uint8_t busNumber, uint8_t screensCount);
    FLProgI2c8bitDisplay(uint8_t screensCount) { setScreensCount(screensCount); };
    void setBusNumber(uint8_t busNumber);
    uint8_t busNumber() { return _device.bus; };
    void setAddress(uint8_t address);
    uint8_t address() { return _device.addr; };
    void setSpeed(uint8_t speed);
    uint8_t speed() { return _device.speed; };

    virtual void pool();

protected:
    bool checkAddress();
     virtual void clearDisplay() ;
    virtual void sendToInterface(uint8_t *sendArray, uint8_t type);
    uint8_t _errorCount = 0;
    uint8_t _oKCount = 0;
    RT_HW_STRUCT_I2C_DEV _device;
};

class FLProgI2c16bitDisplay : public FLProgI2c8bitDisplay

{
public:
    FLProgI2c16bitDisplay() {};
    FLProgI2c16bitDisplay(uint8_t address, uint8_t busNumber, uint8_t screensCount);
    FLProgI2c16bitDisplay(uint8_t screensCount) { setScreensCount(screensCount); };

protected:
};
