#ifndef ENUMS_H
#define ENUMS_H

#include <Arduino.h>

enum BatteryLevels
{
    EMPTY,
    ONE_BAR,
    TWO_BARS,
    THREE_BARS,
    FOUR_BARS,
    FULL,
    CHARGING
};

enum ButtonType
{
    NONE,
    LEFT_ONCE,
    RIGHT_ONCE,
    LEFT_HOLD_2_SECONDS,
};

enum EAMOperation
{
    EAM_INCREASE,
    EAM_DECREASE
};

enum PBOperation
{
    PB_INCREASE,
    PB_DECREASE
};

enum Theme
{
    THEME_BLACK_WHITE,
    THEME_WHITE_BLACK
};

#endif