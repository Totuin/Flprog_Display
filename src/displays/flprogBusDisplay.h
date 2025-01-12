#pragma once
#include "flprogAbstractDisplay.h"

class FLProgBus4Display : public FLProgAbstractTexttDisplay
{
public:
    FLProgBus4Display(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, uint8_t screensCount);
    FLProgBus4Display(uint8_t screensCount) { setScreensCount(screensCount); };
    FLProgBus4Display() {};
    void setRsPin(uint8_t rsPin);
    uint8_t rsPin() { return _rsPin; };
    void setEPin(uint8_t ePin);
    uint8_t ePin() { return _ePin; };
    void setRwPin(uint8_t rwPin);
    uint8_t rwPin() { return _rwPin; };
    void setD4Pin(uint8_t d4Pin);
    uint8_t d4Pin() { return _d4Pin; };
    void setD5Pin(uint8_t d5Pin);
    uint8_t d5Pin() { return _d5Pin; };
    void setD6Pin(uint8_t d6Pin);
    uint8_t d6Pin() { return _d6Pin; };
    void setD7Pin(uint8_t d7Pin);
    uint8_t d7Pin() { return _d7Pin; };
    virtual void setPins(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin);

protected:
    uint8_t _rsPin = 255;
    uint8_t _ePin = 255;
    uint8_t _rwPin = 255;
    uint8_t _d4Pin = 255;
    uint8_t _d5Pin = 255;
    uint8_t _d6Pin = 255;
    uint8_t _d7Pin = 255;
};

class FLProgBus8Display : public FLProgBus4Display
{
public:
    FLProgBus8Display(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d0Pin, uint8_t d1Pin, uint8_t d2Pin, uint8_t d4Pin, uint8_t d3Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, uint8_t screensCount);
    FLProgBus8Display(uint8_t screensCount) { setScreensCount(screensCount); };
    FLProgBus8Display() {};
    uint8_t d0Pin() { return _d0Pin; };
    void setD0Pin(uint8_t d0Pin);
    uint8_t d1Pin() { return _d1Pin; };
    void setD1Pin(uint8_t d1Pin);
    uint8_t d2Pin() { return _d2Pin; };
    void setD2Pin(uint8_t d2Pin);
    uint8_t d3Pin() { return _d3Pin; };
    void setD3Pin(uint8_t d3Pin);
    virtual void setPins(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d0Pin, uint8_t d1Pin, uint8_t d2Pin, uint8_t d4Pin, uint8_t d3Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin);

protected:
    uint8_t _d0Pin = 255;
    uint8_t _d1Pin = 255;
    uint8_t _d2Pin = 255;
    uint8_t _d3Pin = 255;
};