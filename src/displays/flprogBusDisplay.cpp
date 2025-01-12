#include "flprogBusDisplay.h"

FLProgBus4Display::FLProgBus4Display(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setPins(rsPin, ePin, rwPin, d4Pin, d5Pin, d6Pin, d7Pin);
}

void FLProgBus4Display::setRsPin(uint8_t rsPin)
{
    if (rsPin == _rsPin)
    {
        return;
    }
    _rsPin = rsPin;
}

void FLProgBus4Display::setEPin(uint8_t ePin)
{
    if (ePin == _ePin)
    {
        return;
    }
    _ePin = ePin;
}

void FLProgBus4Display::setRwPin(uint8_t rwPin)
{

    if (rwPin == _rwPin)
    {
        return;
    }
    _rwPin = rwPin;
}

void FLProgBus4Display::setD4Pin(uint8_t d4Pin)
{
    if (_d4Pin == d4Pin)
    {
        return;
    }
    _d4Pin = d4Pin;
}

void FLProgBus4Display::setD5Pin(uint8_t d5Pin)
{
    if (_d5Pin == d5Pin)
    {
        return;
    }
    _d5Pin = d5Pin;
}

void FLProgBus4Display::setD6Pin(uint8_t d6Pin)
{
    if (_d6Pin == d6Pin)
    {
        return;
    }
    _d6Pin = d6Pin;
}

void FLProgBus4Display::setD7Pin(uint8_t d7Pin)
{
    if (_d7Pin == d7Pin)
    {
        return;
    }
    _d7Pin = d7Pin;
}

void FLProgBus4Display::setPins(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin)
{
    setRsPin(rsPin);
    setEPin(ePin);
    setRwPin(rwPin);
    setD4Pin(d4Pin);
    setD5Pin(d5Pin);
    setD6Pin(d6Pin);
    setD7Pin(d7Pin);
}

FLProgBus8Display::FLProgBus8Display(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d0Pin, uint8_t d1Pin, uint8_t d2Pin, uint8_t d4Pin, uint8_t d3Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setPins(rsPin, ePin, rwPin, d0Pin, d1Pin, d2Pin, d4Pin, d3Pin, d5Pin, d6Pin, d7Pin);
}

void FLProgBus8Display::setD0Pin(uint8_t d0Pin)
{
    if (_d0Pin == d0Pin)
    {
        return;
    }
    _d0Pin = d0Pin;
}

void FLProgBus8Display::setD1Pin(uint8_t d1Pin)
{
    if (_d1Pin == d1Pin)
    {
        return;
    }
    _d1Pin = d1Pin;
}

void FLProgBus8Display::setD2Pin(uint8_t d2Pin)
{
    if (_d2Pin == d2Pin)
    {
        return;
    }
    _d2Pin = d2Pin;
}

void FLProgBus8Display::setD3Pin(uint8_t d3Pin)
{
    if (_d3Pin == d3Pin)
    {
        return;
    }
    _d3Pin = d3Pin;
}

void FLProgBus8Display::setPins(uint8_t rsPin, uint8_t ePin, uint8_t rwPin, uint8_t d0Pin, uint8_t d1Pin, uint8_t d2Pin, uint8_t d4Pin, uint8_t d3Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin)
{
    FLProgBus4Display::setPins(rsPin, ePin, rwPin, d4Pin, d5Pin, d6Pin, d7Pin);
    setD0Pin(d0Pin);
    setD1Pin(d1Pin);
    setD2Pin(d2Pin);
    setD3Pin(d3Pin);
}