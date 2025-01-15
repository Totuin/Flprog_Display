#include "RT_HW_CONSOLE.h"
#include "flprogDisplay.h"

RT_HW_PIN_DIR_ID idPinLed(RT_HW_Base.getPinLed(), 0, 'N'); //--Пин LED на плате;
uint8_t isInit = 0;

FLProgI2c8bitDisplay lcdDisplay(0x27, 0, 1);
FLProgTextDisplayScreen firstScreen(2);
FLProgTextDisplayTextField firstField(1, 1, "Screen 1");
FLProgTextDisplayTextField firstField1(1, 2, "Test1");

FLProgTextDisplayScreen secondScreen(2);
FLProgTextDisplayTextField secondField(1, 1, "Screen 2");
FLProgTextDisplayTextField secondField1(1, 2, "Test2");

void setup()
{
}

void loop()
{

    if (isInit == 0)
    {
        RT_HW_console.setParam(0, 115200);
        RT_HW_console.begin();
        if (!RT_HW_console.getOk())
        {
            return;
        }
        RT_HW_console.outTest(String(F("1.Start LCD adr")), lcdDisplay.address());
        isInit = 1;
    }

    if (isInit == 1)
    {
        lcdDisplay.addScreen(&firstScreen);
        firstScreen.addField(&firstField);
        firstScreen.addField(&firstField1);

        lcdDisplay.addScreen(&secondScreen);
        secondScreen.addField(&secondField);
        secondScreen.addField(&secondField1);

        isInit = 2;
        RT_HW_console.outTest(String(F("2.Start LCD adr")), lcdDisplay.address(), 'E', 'H');
    }
    //========================================
    RT_HW_Base.sheduler();
    RT_HW_Base.pinDigitalWrite(idPinLed, RT_HW_Base.shed.blink500);

    lcdDisplay.pool();
    if (lcdDisplay.getIsChangeStatus())
    {
        RT_HW_console.outTest(String(F("NewStatus - ")), lcdDisplay.getStatus());
        lcdDisplay.resetIsChangeStatus();
    }

    if (lcdDisplay.getIsChangeError())
    {
        RT_HW_console.outTest(String(F("NewError - ")), lcdDisplay.getStatus());
        lcdDisplay.resetIsChangeError();
    }

    lcdDisplay.light(RT_HW_Base.shed.blink250);
    firstScreen.enable(RT_HW_Base.shed.blink1000);
    secondScreen.enable(!RT_HW_Base.shed.blink1000);
}