#ifndef PAGETEMPLATE_H
#define PAGETEMPLATE_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "H_StructConstants.h"
#include "H_Utils.h"

enum TextPositions
{
    LEFT,
    RIGHT
};

class PageTemplate
{
private:
    TFT_eSPI &tft;

public:
    PageTemplate(TFT_eSPI &display);
    void tftInit();
    void drawStatusBar();
    void drawStatusBar(String title);
    void drawTitle(String title);
    void drawButtons(TextPositions position, String button);
    void drawButtons(String leftButton, String rightButton);
    void drawButtons(String leftButton, String rightButton, bool condition);
    void drawOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption);
    void drawOptions(LabelValuePageOptionsStruct options[], int optionsCount, int selectedOption, String currentValue);
    void drawOptions(LabelIntValueLimitPageOptionsStruct options[], int optionsCount, int selectedOption, uint16_t selectedOptionFontColor, String optionName, bool condition);
};

#endif