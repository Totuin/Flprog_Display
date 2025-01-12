
#pragma once
#include "flprogAbstractDisplay.h"

class FLProgSpiDisplay : public FLProgAbstractTexttDisplay
{
public:
    FLProgSpiDisplay(uint8_t csPin, uint8_t busNumber, uint8_t screensCount);
    FLProgSpiDisplay(uint8_t screensCount) { setScreensCount(screensCount); };
    FLProgSpiDisplay() {};
    void setBusNumber(uint8_t busNumber);
    uint8_t busNumber() { return _busNumber; };
    void setCsPin(uint8_t csPin);
    uint8_t csPin() { return _csPin; };

protected:
    uint8_t _busNumber = 0;
    uint8_t _csPin = 255;
};
