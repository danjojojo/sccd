#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#include "../constants/enums.h"
#include "../constants/globals.h"

Theme getThemeFromString(String name);
BatteryLevels getBatteryLevel(float voltage);
Orientations getOrientation(String ort);

void getItemsPerPage(int optionsCount);

template <typename T, size_t N>
int getOptionsCount(T (&array)[N])
{
    return N;
}
int listOptionsPadding(int optionIndex);

#endif