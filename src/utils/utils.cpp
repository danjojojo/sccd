#include "../include/utils/utils.h"

// RETURNS
Theme getThemeFromString(String str)
{
    if (str == "BLACK_WHITE")
        return THEME_BLACK_WHITE;
    if (str == "WHITE_BLACK")
        return THEME_WHITE_BLACK;
    return THEME_BLACK_WHITE;
}

BatteryLevels getBatteryLevel(float voltage)
{
    if (VOLTAGE < 3.0)
        return EMPTY;
    if (VOLTAGE >= 3.0 && VOLTAGE < 3.3)
        return ONE_BAR;
    if (VOLTAGE >= 3.3 && VOLTAGE < 3.6)
        return TWO_BARS;
    if (VOLTAGE >= 3.6 && VOLTAGE < 3.9)
        return THREE_BARS;
    if (VOLTAGE >= 3.9 && VOLTAGE < 4.2)
        return FOUR_BARS;
    if (VOLTAGE >= 4.2)
        return CHARGING;
    return EMPTY;
}

Orientations getOrientation(String ort)
{
    if (ort == "P1")
        return P1;
    if (ort == "P2")
        return P2;
    if (ort == "L1")
        return L1;
    if (ort == "L2")
        return L2;
    return P1;
}

int listOptionsPadding(int optionIndex)
{
    if (CURRENT_ORIENTATION == "P1" || CURRENT_ORIENTATION == "P2")
    {
        return (35 * (optionIndex + 1) + 10);
    }
    else if (CURRENT_ORIENTATION == "L1" || CURRENT_ORIENTATION == "L2")
    {
        return (20 * (optionIndex + 1) + 10);
    }
}

void getItemsPerPage(int optionsCount)
{
    if (optionsCount <= PAGE_ITEMS_LIMIT)
    {
        return;
    }

    PAGES = 0;
    START_COUNT = 0;
    for (int i = 0; i < MAX_PAGES; i++)
    {
        COLUMNS[i] = 0;
    }

    PAGES = ceil(optionsCount / PAGE_ITEMS_LIMIT);
    COLUMNS[0] = PAGE_ITEMS_LIMIT;

    for (int i = 1; i <= PAGES; i++)
    {
        int rem = optionsCount - PAGE_ITEMS_LIMIT;
        if (rem < PAGE_ITEMS_LIMIT)
        {
            COLUMNS[i] = rem;
        }
        else
        {
            COLUMNS[i] = rem - (rem - PAGE_ITEMS_LIMIT);
            optionsCount = rem;
        }
    }
}