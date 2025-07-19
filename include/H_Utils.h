#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include "H_Enums.h"
#include "H_Globals.h"

Theme getThemeFromString(String name);
BatteryLevels getBatteryLevel(float voltage);
int listOptionsPadding(int optionIndex);

template <typename T, size_t N>
int getOptionsCount(T (&array)[N])
{
    return N;
}

#endif