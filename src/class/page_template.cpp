#include "../include/class/page_template.h"

PageTemplate::PageTemplate(TFT_eSPI &display)
    : tft(display)
{
}

void PageTemplate::tftInit()
{
    tft.setRotation(DISPLAY_ROTATION);
    tft.fillScreen(BG_COLOR);
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.setTextWrap(true, false);
    tft.setSwapBytes(true);
}

void PageTemplate::drawStatusBar()
{
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.fillRect(0, 0, tft.width(), 25, BG_COLOR);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    tft.setTextDatum(TL_DATUM);
    tft.drawString(CONNECTION_SIGNAL, 0, 0);
    tft.setTextDatum(TR_DATUM);
    drawBattery();
}

void PageTemplate::drawStatusBar(String title)
{
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.fillRect(0, 0, tft.width(), 25, BG_COLOR);
    tft.setTextDatum(TL_DATUM);
    tft.drawString(title, 0, 0);
    tft.setTextDatum(TR_DATUM);
    drawBattery();
}

void PageTemplate::drawTitle(String title)
{
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(&Orbitron_Regular12pt7b);
    tft.drawString(title, tft.width() / 2, tft.height() / 2);
}

void PageTemplate::drawTitle(String title, int away)
{
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(&Orbitron_Regular12pt7b);
    tft.drawString(title, tft.width() / 2, (tft.height() / 2) + away);
}

void PageTemplate::drawButtons(TextPositions position, String button)
{
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    switch (position)
    {
    case LEFT:
        tft.setTextDatum(BL_DATUM);
        tft.drawString(button, 5, tft.height() - 5);
        break;
    case RIGHT:
        tft.setTextDatum(BR_DATUM);
        tft.drawString(button, tft.width() - 5, tft.height() - 5);
        break;
    default:
        break;
    }
}

void PageTemplate::drawButtons(String leftButton, String rightButton)
{
    tft.fillRect(0, tft.height() - 25, tft.width(), 30, BG_COLOR);
    drawButtons(LEFT, leftButton);
    drawButtons(RIGHT, rightButton);
}

void PageTemplate::drawButtons(String leftButton, String rightButton, bool condition)
{
    tft.fillRect(0, tft.height() - 25, tft.width(), 30, BG_COLOR);
    drawButtons(LEFT, condition ? "Dec" : leftButton);
    drawButtons(RIGHT, condition ? "Inc" : rightButton);
}

void PageTemplate::drawOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption, bool addArrow)
{
    refreshScreen();
    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    for (int i = 0; i < optionsCount; i++)
    {
        if (addArrow)
        {
            drawSelectedOptionWithArrow(i, selectedOption, i);
        }
        else
        {
            drawSelectedOption(i, selectedOption);
        }
        tft.drawString(options[i].label, 20, listOptionsPadding(i));
    }
}

void PageTemplate::drawOptions(LabelValuePageOptionsStruct options[], int optionsCount, int selectedOption, String currentValue)
{
    refreshScreen();
    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    for (int i = 0; i < optionsCount; i++)
    {
        drawSelectedOption(i, selectedOption);

        String label = options[i].label;
        String value = options[i].value;
        if (value == currentValue)
        {
            label += " <<";
        }
        tft.drawString(label, 5, listOptionsPadding(i));
    }
}

void PageTemplate::drawOptions(LabelIntValueLimitPageOptionsStruct options[], int optionsCount, int selectedOption, uint16_t selectedOptionFontColor, String optionName, bool condition)
{
    refreshScreen();
    tft.setFreeFont(&ChakraPetch_Bold16pt7b);

    int optLabelYPos = 35;
    int optValueYPos = 65;

    int exitY = 100;

    int optsCountWithoutExit = optionsCount - 1;
    int xPos = (tft.width() / optsCountWithoutExit) / 2;
    int xInterval = tft.width() / optsCountWithoutExit;

    for (int i = 0; i < optionsCount; i++)
    {
        String label = options[i].label;
        tft.setTextColor(i == selectedOption ? FG_COLOR : TFT_DARKGREY, BG_COLOR);

        if (label != "Exit")
        {
            tft.setFreeFont(&ChakraPetch_Bold16pt7b);
            tft.setTextDatum(MC_DATUM);
            Serial.print("x Pos: ");
            Serial.println(xPos + (i * xInterval));
            tft.drawString(label, xPos + (i * xInterval), optLabelYPos);
        }
        else
        {
            tft.setFreeFont(&ChakraPetch_Regular8pt7b);
            tft.setTextDatum(ML_DATUM);
            tft.drawString(label, 5, exitY);
        }

        if (options[i].value != nullptr)
        {
            condition &&optionName == label ? tft.setTextColor(selectedOptionFontColor) : tft.setTextColor(TFT_DARKGREY);
            tft.setFreeFont(&Vipnagorgialla_Rg17pt7b);
            tft.drawNumber(*options[i].value, xPos + (i * xInterval), optValueYPos);
        }
    }
}

void PageTemplate::drawPaginatedOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption, bool addArrow)
{
    if (optionsCount <= PAGE_ITEMS_LIMIT)
        return drawOptions(options, optionsCount, selectedOption, addArrow);

    if (selectedOption != 0 && selectedOption % PAGE_ITEMS_LIMIT == 0)
    {
        CURRENT_PAGE += 1;
    }
    else if (selectedOption == 0)
    {
        CURRENT_PAGE = 0;
    }

    START_COUNT = CURRENT_PAGE * PAGE_ITEMS_LIMIT;
    int addArrowGap = addArrow ? 20 : 5;

    refreshScreen();
    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    for (int i = START_COUNT; i < START_COUNT + COLUMNS[CURRENT_PAGE]; i++)
    {
        if (addArrow)
        {
            drawSelectedOptionWithArrow(i, selectedOption, i % PAGE_ITEMS_LIMIT);
        }
        else
        {
            drawSelectedOption(i, selectedOption);
        }
        tft.drawString(options[i].label, addArrowGap, listOptionsPadding(i % PAGE_ITEMS_LIMIT));
    }
    drawPageArrow();
}

void PageTemplate::drawLogs(int logsCount, int selectedLogNum)
{
    refreshScreen();
    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);

    if (logsCount == 0)
    {
        tft.setTextColor(TFT_DARKGREY);
        tft.drawString("No logs here.", 5, listOptionsPadding(0));
        return;
    }

    int line = 0;
    for (int i = logsCount - 1; i >= 0; i--)
    {
        drawSelectedOption(i, selectedLogNum);
        tft.drawString(TIMER_LOGS[i], 5, listOptionsPadding(line));
        line++;
    }
}

void PageTemplate::drawPaginatedLogs(int logsCount, int selectedLogNum)
{

    if (logsCount <= PAGE_ITEMS_LIMIT)
        return drawLogs(logsCount, selectedLogNum);

    bool logsCountIsEven = (logsCount - 1) % 2 == 0;

    if (selectedLogNum != logsCount - 1 && selectedLogNum == START_COUNT - PAGE_ITEMS_LIMIT)
    {
        CURRENT_PAGE += 1;
    }
    else if (selectedLogNum == logsCount - 1)
    {
        CURRENT_PAGE = 0;
    }

    START_COUNT = (logsCount - 1) - (CURRENT_PAGE * PAGE_ITEMS_LIMIT);

    refreshScreen();
    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);

    int line = 0;
    for (int i = START_COUNT; i > START_COUNT - COLUMNS[CURRENT_PAGE]; i--)
    {
        drawSelectedOption(i, selectedLogNum);
        tft.drawString(TIMER_LOGS[i], 5, listOptionsPadding(line % PAGE_ITEMS_LIMIT));
        Serial.println(TIMER_LOGS[i]);
        line++;
    }
    drawPageArrow();
}

// REUSABLE

void PageTemplate::drawSelectedOption(int index, int selectedOption)
{
    if (index == selectedOption)
    {
        tft.setTextColor(FG_COLOR, BG_COLOR);
    }
    else
    {
        tft.setTextColor(TFT_DARKGREY, BG_COLOR);
    }
}

void PageTemplate::drawSelectedOptionWithArrow(int index, int selectedOption, int position)
{
    if (index == selectedOption)
    {
        tft.setTextColor(FG_COLOR, BG_COLOR);
        tft.drawString("> ", 5, listOptionsPadding(position));
        tft.setTextColor(FG_COLOR, BG_COLOR);
    }
    else
    {
        tft.setTextColor(TFT_DARKGREY, BG_COLOR);
    }
}

void PageTemplate::refreshScreen()
{
    tft.fillRect(0, 20, tft.width(), REFRESH_HEIGHT, BG_COLOR);
}

void PageTemplate::drawPageArrow()
{
    if (CURRENT_PAGE != PAGES)
    {
        int aX = tft.width() - 30;
        int aY = tft.height() - 35;

        int bX = (tft.width() - 30) - 7;
        int bY = tft.height() - 45;

        int cX = (tft.width() - 30) + 7;
        int cY = tft.height() - 45;

        tft.fillTriangle(aX, aY, bX, bY, cX, cY, TFT_DARKGREY);
    }
}

void PageTemplate::drawBattery(){
    int batteryBars = 5;
    if (BATTERY_LEVEL != 6)
    {
        for (int i = 1; i <= batteryBars; i++)
        {
            tft.fillRect(145 + (i * 15), 5, 10, 10, i <= BATTERY_LEVEL ? FG_COLOR : TFT_DARKGREY);
            Serial.print(i <= BATTERY_LEVEL ? "O" : "X");
        }
    } else {
        for (int i = 1; i <= batteryBars; i++)
        {
            tft.fillRect(145 + (i * 15), 5, 10, 10, TFT_GREEN);
        }
    }
}