#include "flprogDisplay.h"

FLProgI2c8bitDisplay lcdDisplay(0x27, 0, 3);
FLProgTextDisplayScreen screen1(2);
FLProgTextDisplayScreen *tempScreen;

void setup()
{
    lcdDisplay.addScreen(&screen1);
    lcdDisplay.createScreen(3);
    lcdDisplay.createScreen(10, 2);
    tempScreen = lcdDisplay.screenAt(1);
}

void loop()
{
    lcdDisplay.pool();
}