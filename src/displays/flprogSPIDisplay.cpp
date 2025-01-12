#include "flprogSPIDisplay.h"

FLProgSpiDisplay::FLProgSpiDisplay(uint8_t csPin, uint8_t busNumber, uint8_t screensCount)
{
    setScreensCount(screensCount);
    setBusNumber(busNumber);
    setCsPin(csPin);
}

void FLProgSpiDisplay::setBusNumber(uint8_t busNumber)
{
    if (busNumber == _busNumber)
    {
        return;
    }
    _busNumber = busNumber;
}

void FLProgSpiDisplay::setCsPin(uint8_t csPin)
{
    if (csPin == _csPin)
    {
        return;
    }
    _csPin = csPin;
}