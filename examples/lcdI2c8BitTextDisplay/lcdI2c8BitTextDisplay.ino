#include "flprogDisplay.h"

FLProgI2c8bitDisplay lcdDisplay(0x27, 0, 1);
FLProgTextDisplayScreen firstScreen(1);
FLProgTextDisplayTextField firstField(1, 5, "Test");

void setup()
{
    Serial.begin(115200);
    lcdDisplay.addScreen(&firstScreen);
    firstScreen.addField(&firstField);
    firstScreen.enable(true);
}

void loop()
{
    lcdDisplay.pool();
}