#pragma once
#include <Arduino.h>
#include "flprogUtilites.h"
#include "../screens/flprogDisplayScreen.h"

#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP 0
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_SET_CURSOR_STEP 1
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_SEND_DATA_STEP 2

#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND 0
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_DATA_COMMAND 1
#define FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND 2

#define FLPROG_TEXT_DISPLAY_INIT_DISPLAY_START_STEP 0
#define FLPROG_TEXT_DISPLAY_INIT_DISPLAY_DELAY_STEP 1
#define FLPROG_TEXT_DISPLAY_INIT_DISPLAY_NEXT_CODE_STEP 2

static const unsigned char RT_HW_LCD44780_INIT_BUS4[] PROGMEM =
    {
        0b00000011, FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND, 45,
        0b00000011, FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND, 45,
        0b00000011, FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND, 45,
        0b00000010, FLPROG_TEXT_DISPLAY_SEND_BUFFER_TETRA_COMMAND, 20,
        0b00100000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00000001, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00000100, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00101000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00010000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00001100, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00000110, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00000001, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20};

static const unsigned char RT_HW_LCD44780_INIT_BUS8[] PROGMEM =
    {
        0b00110000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 45,
        0b00110000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1,
        0b00110000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1,
        0b00111000, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1,
        0b00001110, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1,
        0b00000001, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 20,
        0b00000110, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1,
        0b00001100, FLPROG_TEXT_DISPLAY_SEND_BUFFER_INSTRUCTION_COMMAND, 1};


struct FLProgTextFieldSendBuffer
{
    String buffer = "";
    uint8_t row = 255;
    uint8_t col = 255;
    uint8_t pointCursor = 0;
    uint8_t pointer = 0;
};

class FLProgAbstractDisplay : public AbstractFLProgClass
{
public:
    void setRestartPeriod(uint32_t restartPeriod) { _restartPeriod = restartPeriod; };
    uint32_t restartPeriod() { return _restartPeriod; };
    uint8_t screensCount() { return _screensCount; };
    virtual void pool() {};

protected:
    virtual void clearDisplay() {};
    virtual bool initDisplay() { return true; };
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
    bool setEnableScreen();
    void light(bool value);

    void setRows(uint8_t rows) { _rows = rows; };
    void setCoils(uint8_t cols) { _cols = cols; };
    uint8_t rows() { return _rows; };
    uint8_t coils() { return _cols; };

    uint8_t chipCount();

protected:
    FLProgTextDisplayScreen **_screens;
    FLProgTextDisplayScreen *_enableScreen = 0;
    void setScreensCount(uint8_t screensCount);
    uint8_t rowIffset();
    void setCursorPointToBuffer();

    void prepareSendArray(uint8_t value, uint8_t type);
    void privatePrepareSendArray(uint8_t chip, uint8_t value, uint8_t type);

    void showScreen();
    bool sendBuffer();
    bool setCursor();
    bool sendBufferString();
    virtual bool initDisplay();
    void sendLight();
    bool initLcd4OneChip();
    bool initLcd8OneChip();
    bool initLcd4TwoChip();
    bool initLcd8TwoChip();

    virtual uint8_t bitRS() { return 0; };
    virtual uint8_t bitRW() { return 1; };
    virtual uint8_t bitE() { return 2; };
    virtual uint8_t bitOn() { return 3; };

    virtual uint8_t bitCount() { return 4; };
    void clearSendArray();

    virtual void sendToInterface(uint8_t type) { (void)type; };

    bool _lightOn = true;
    bool _isNeedUpdateLight = true;
    uint8_t _rows = 2;
    uint8_t _cols = 16;
    uint8_t _sendBufferStep = FLPROG_TEXT_DISPLAY_SEND_BUFFER_START_STEP;
    uint8_t _initDisplayStep = FLPROG_TEXT_DISPLAY_INIT_DISPLAY_START_STEP;
    uint8_t _initDisplayStepIndex = 0;
    uint8_t _sendArray[4];
    FLProgTextFieldSendBuffer _buffer;
};

#include "displays/flprogI2cDisplay.h"
#include "displays/flprogSPIDisplay.h"
#include "displays/flprogSPNDisplay.h"
#include "displays/flprogBusDisplay.h"
