#include "../include/class/page_template.h"

PageTemplate::PageTemplate(TFT_eSPI &display)
    : tft(display)
{
}

void PageTemplate::tftInit()
{
    tft.setRotation(DISPLAY_ROTATION);
    tft.fillScreen(BG_COLOR);
    tft.setTextColor(FG_COLOR);
    tft.setCursor(0, 0, 2);
    tft.setTextSize(1);
    tft.setTextWrap(true, false);
}

void PageTemplate::drawStatusBar()
{
    tft.fillRect(0, 0, tft.width(), 20, BG_COLOR);
    tft.setTextColor(FG_COLOR);
    tft.setTextDatum(TL_DATUM);
    tft.drawString(CONNECTION_SIGNAL, 0, 0);
    tft.setTextDatum(TR_DATUM);
    tft.drawString(BATTERY_LEVEL, tft.width(), 0);
}

void PageTemplate::drawStatusBar(String title)
{
    tft.setTextColor(FG_COLOR);
    tft.setTextDatum(TL_DATUM);
    tft.drawString(title, 0, 0);
    tft.setTextDatum(TR_DATUM);
    tft.drawString(BATTERY_LEVEL, tft.width(), 0);
}

void PageTemplate::drawTitle(String title)
{
    tft.setTextDatum(MC_DATUM);
    tft.drawString(title, tft.width() / 2, tft.height() / 2);
}

void PageTemplate::drawButtons(TextPositions position, String button)
{
    switch (position)
    {
    case LEFT:
        tft.setTextDatum(BL_DATUM);
        tft.drawString(button, 0, tft.height());
        break;
    case RIGHT:
        tft.setTextDatum(BR_DATUM);
        tft.drawString(button, tft.width(), tft.height());
        break;
    default:
        break;
    }
}

void PageTemplate::drawButtons(String leftButton, String rightButton)
{
    tft.setTextDatum(BL_DATUM);
    tft.drawString(leftButton, 0, tft.height());
    tft.setTextDatum(BR_DATUM);
    tft.drawString(rightButton, tft.width(), tft.height());
}

void PageTemplate::drawButtons(String leftButton, String rightButton, bool condition)
{
    tft.fillRect(0, tft.height() - 30, tft.width(), 30, BG_COLOR);
    tft.setTextColor(FG_COLOR);
    tft.setTextDatum(BL_DATUM);
    tft.drawString(condition ? "Decrease" : leftButton, 0, tft.height());
    tft.setTextDatum(BR_DATUM);
    tft.drawString(condition ? "Increase" : rightButton, tft.width(), tft.height());
}

void PageTemplate::drawOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption)
{
    tft.fillRect(0, 100, tft.width(), 30, BG_COLOR);
    tft.setTextDatum(ML_DATUM);
    for (int i = 0; i < optionsCount; i++)
    {
        if (i == selectedOption)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.drawString(options[i].label, 5, listOptionsPadding(i));
    }
}

void PageTemplate::drawOptions(LabelValuePageOptionsStruct options[], int optionsCount, int selectedOption, String currentValue)
{
    tft.fillRect(0, 100, tft.width(), 30, BG_COLOR);
    tft.setTextDatum(ML_DATUM);
    for (int i = 0; i < optionsCount; i++)
    {
        if (i == selectedOption)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }

        String label = options[i].label;
        String value = options[i].value;
        if (value == currentValue)
        {
            label += " (using)";
        }
        tft.drawString(label, 5, listOptionsPadding(i));
    }
}

void PageTemplate::drawOptions(LabelIntValueLimitPageOptionsStruct options[], int optionsCount, int selectedOption, uint16_t selectedOptionFontColor, String optionName, bool condition)
{
    tft.fillRect(0, 30, tft.width(), 150, BG_COLOR);
    for (int i = 0; i < optionsCount; i++)
    {
        if (i == selectedOption)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.setTextDatum(ML_DATUM);
        tft.drawString(options[i].label, 5, listOptionsPadding(i));

        tft.setTextDatum(MR_DATUM);
        if (options[i].value != nullptr)
        {
            condition &&optionName == options[i].label ? tft.setTextColor(selectedOptionFontColor) : tft.setTextColor(TFT_DARKGREY);
            tft.drawNumber(*options[i].value, tft.width(), listOptionsPadding(i));
        }
    }
}

void PageTemplate::drawPaginatedOptions(LabelPageOptionsStruct options[], int optionsCount, int selectedOption)
{

    if (optionsCount <= PAGE_LIMIT)
        return drawOptions(options, optionsCount, selectedOption);

    if (selectedOption != 0 && selectedOption % PAGE_LIMIT == 0)
    {
        CURRENT_PAGE += 1;
    }
    else if (selectedOption == 0)
    {
        CURRENT_PAGE = 0;
    }

    int startCount = CURRENT_PAGE * PAGE_LIMIT;

    tft.fillRect(0, 20, tft.width(), 180, BG_COLOR);
    tft.setTextDatum(ML_DATUM);
    for (int i = startCount; i < startCount + COLUMNS[CURRENT_PAGE]; i++)
    {
        if (i == selectedOption)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.drawString(options[i].label, 5, listOptionsPadding(i % PAGE_LIMIT));
    }
}

void PageTemplate::drawLogs(int logsCount, int selectedLogNum)
{
    tft.fillRect(0, 100, tft.width(), 30, BG_COLOR);
    tft.setTextDatum(ML_DATUM);

    if (logsCount == 0)
    {
        tft.setTextColor(TFT_DARKGREY);
        tft.drawString("No logs here.", 5, listOptionsPadding(0));
        return;
    }

    int line = 0;
    for (int i = logsCount - 1; i >= 0; i--)
    {
        if (i == selectedLogNum)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.drawString(TIMER_LOGS[i], 5, listOptionsPadding(line));
        line++;
    }
}

void PageTemplate::drawPaginatedLogs(int logsCount, int selectedLogNum)
{

    if (logsCount <= PAGE_LIMIT)
        return drawLogs(logsCount, selectedLogNum);

    bool logsCountIsEven = (logsCount - 1) % 2 == 0;
    int remainder = logsCountIsEven ? 0 : 1;

    if (selectedLogNum != logsCount - 1 && selectedLogNum % PAGE_LIMIT == remainder)
    {
        CURRENT_PAGE += 1;
    }
    else if (selectedLogNum == logsCount - 1)
    {
        CURRENT_PAGE = 0;
    }

    int startCount = (logsCount - 1) - (CURRENT_PAGE * PAGE_LIMIT);

    tft.fillRect(0, 20, tft.width(), 180, BG_COLOR);
    tft.setTextDatum(ML_DATUM);

    int line = 0;
    for (int i = startCount; i > startCount - COLUMNS[CURRENT_PAGE]; i--)
    {
        if (i == selectedLogNum)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.drawString(TIMER_LOGS[i], 5, listOptionsPadding(line % PAGE_LIMIT));
        line++;
    }
}