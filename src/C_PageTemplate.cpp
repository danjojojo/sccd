#include "C_PageTemplate.h"

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
