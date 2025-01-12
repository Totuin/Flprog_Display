#pragma once
#include "flprogAbstractDisplay.h"

class FLProgSpnDisplay : public FLProgAbstractTexttDisplay
{
public:
    FLProgSpnDisplay(uint8_t csPin, uint8_t sckPin, uint8_t mosiPin, uint8_t misoPin, uint8_t screensCount);
    FLProgSpnDisplay(uint8_t screensCount) { setScreensCount(screensCount); };

    void setCsPin(uint8_t csPin);
    uint8_t csPin() { return _csPin; };
    void setSckPin(uint8_t sckPin);
    uint8_t sckPin() { return _sckPin; };
    void setMosiPin(uint8_t mosiPin);
    uint8_t mosiPin() { return _mosiPin; };
    void setMisoPin(uint8_t misoPin);
    uint8_t misoPin() { return _misoPin; };
    void setPins(uint8_t sckPin, uint8_t mosiPin, uint8_t misoPin, uint8_t csPin);

protected:
    uint8_t _sckPin = 255;
    uint8_t _mosiPin = 255;
    uint8_t _misoPin = 255;
    uint8_t _csPin = 255;
};
