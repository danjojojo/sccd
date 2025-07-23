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

int listOptionsPadding(int optionIndex)
{
    return (40 * (optionIndex + 1) + 10);
}

void getItemsPerPage(int optionsCount)
{
    PAGES = 0;
    for (int i = 0; i < MAX_PAGES; i++)
    {
        COLUMNS[i] = 0;
    }

    PAGES = ceil(optionsCount / PAGE_LIMIT);
    COLUMNS[0] = PAGE_LIMIT;

    for (int i = 1; i <= PAGES; i++)
    {
        int rem = optionsCount - PAGE_LIMIT;
        if (rem < PAGE_LIMIT)
        {
            COLUMNS[i] = rem;
        }
        else
        {
            COLUMNS[i] = rem - (rem - PAGE_LIMIT);
            optionsCount = rem;
        }
    }
}