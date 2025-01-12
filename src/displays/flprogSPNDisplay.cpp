#include "flprogSPNDisplay.h"

FLProgSpnDisplay::FLProgSpnDisplay(uint8_t csPin, uint8_t sckPin, uint8_t mosiPin, uint8_t misoPin, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setPins(sckPin, mosiPin, misoPin, csPin);
}

void FLProgSpnDisplay::setCsPin(uint8_t csPin)
{
    if (csPin == _csPin)
    {
        return;
    }
    _csPin = csPin;
}

void FLProgSpnDisplay::setSckPin(uint8_t sckPin)
{
    if (_sckPin == sckPin)
    {
        return;
    }
    _sckPin = sckPin;
}

void FLProgSpnDisplay::setMosiPin(uint8_t mosiPin)
{
    if (_mosiPin == mosiPin)
    {
        return;
    }
    _mosiPin = mosiPin;
}

void FLProgSpnDisplay::setMisoPin(uint8_t misoPin)
{
    if (_misoPin == misoPin)
    {
        return;
    }
    _misoPin = misoPin;
}

void FLProgSpnDisplay::setPins(uint8_t sckPin, uint8_t mosiPin, uint8_t misoPin, uint8_t csPin)
{
    setSckPin(sckPin);
    setMosiPin(mosiPin);
    setMisoPin(misoPin);
    setCsPin(csPin);
}