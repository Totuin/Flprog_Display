#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "../screens/flprogDisplayScreen.h"

#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP 0
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_WAIT_SET_CURSOR_STEP 1
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_SEND_DATA_STEP 2

#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND 0
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND 1
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND 2

class FLProgAbstractDisplay : public AbstractFLProgClass
{
public:
    void setRestartPeriod(uint32_t restartPeriod) { _restartPeriod = restartPeriod; };
    uint32_t restartPeriod() { return _restartPeriod; };

    virtual void pool() {};

protected:
    virtual void clearDisplay() {};
    virtual void showScreen() {};
    uint32_t _restartPeriod = 0;
    uint32_t lastRestartTime;
    uint8_t _screensCount = 0;
    uint16_t _delayValue = 100;
    uint32_t _delayStartTime;
};

class FLProgAbstractTexttDisplay : public FLProgAbstractDisplay
{
public:
    void addScreen(FLProgTextDisplayScreen *screen);
    void createScreen(uint8_t fieldsCounts);
    void createScreen(uint8_t fieldsCounts, uint8_t index);
    FLProgTextDisplayScreen *screenAt(uint8_t index);
    void setEnableScreen();

    void setRows(uint8_t rows) { _rows = rows; };
    void setCoils(uint8_t cols) { _cols = cols; };
    uint8_t rows() { return _rows; };
    uint8_t coils() { return _cols; };

protected:
    FLProgTextDisplayScreen **_screens;
    FLProgTextDisplayScreen *_enableScreen = 0;
    void setScreensCount(uint8_t screensCount);
    uint8_t freeScreenIndex();
    uint8_t rowIffset();
    uint8_t chipCount();
    void setCursorPointToBuffer();
    void sendBuffer();
    void prepareSendArray(uint8_t *sendArray, uint8_t value, uint8_t type);
    void setCursor();
    void sendBufferString();
    
    virtual uint8_t bitRS() { return 0; };
    virtual uint8_t bitRW() { return 1; };
    virtual uint8_t bitE() { return 2; };
    virtual uint8_t bitOn() { return 3; };

    virtual void sendToInterface(uint8_t *sendArray, uint8_t type);
    virtual void showScreen();

    bool lightOn = true;
    uint8_t _rows = 2;
    uint8_t _cols = 16;
    uint8_t _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
    FLProgTextFieldSendBuffer *_buffer;
};

#include "displays/flprogI2cDisplay.h"
#include "displays/flprogSPIDisplay.h"
#include "displays/flprogSPNDisplay.h"
#include "displays/flprogBusDisplay.h"
