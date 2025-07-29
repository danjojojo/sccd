#ifndef PAGE_TEMPLATE_H
#define PAGE_TEMPLATE_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "../constants/structs.h"
#include "../utils/utils.h"

#include "../fonts/ChakraPetch_Regular8pt7b.h"
#include "../fonts/ChakraPetch_Bold8pt7b.h"
#include "../fonts/ChakraPetch_Bold16pt7b.h"

#include "../fonts/Orbitron_Regular12pt7b.h"

#include "../fonts/Vipnagorgialla_Rg10pt7b.h"
#include "../fonts/Vipnagorgialla_Rg13pt7b.h"
#include "../fonts/Vipnagorgialla_Rg17pt7b.h"
#include "../fonts/Vipnagorgialla_Rg21pt7b.h"
#include "../fonts/Vipnagorgialla_Rg24pt7b.h"

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
    void drawTitle(String title, int away);
    
    void drawButtons(TextPositions position, String button);
    void drawButtons(String leftButton, String rightButton);
    void drawButtons(String leftButton, String rightButton, bool condition);

    void drawSelectedOption(int index, int selectedOption);
    void drawSelectedOptionWithArrow(int index, int selectedOption, int position);
    void refreshScreen();
    void drawPageArrow();
    void drawBattery();

    void drawOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption, bool addArrow);
    void drawOptions(LabelValuePageOptionsStruct options[], int optionsCount, int selectedOption, String currentValue);
    void drawOptions(LabelIntValueLimitPageOptionsStruct options[], int optionsCount, int selectedOption, uint16_t selectedOptionFontColor, String optionName, bool condition);

    void drawLogs(int logsCount, int selectedLogNum);

    void drawPaginatedOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption, bool addArrow);
    void drawPaginatedLogs(int logsCount, int selectedLogNum);
};

#endif