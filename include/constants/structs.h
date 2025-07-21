#ifndef STRUCTS_H
#define STRUCTS_H

#include "../class/page.h"

struct LabelPageOptionsStruct
{
    const char *label;
    Page *targetPage;
};

struct LabelValuePageOptionsStruct
{
    const char *label;
    const char *value;
    Page *targetPage;
};

struct LabelIntValueLimitPageOptionsStruct
{
    const char *label;
    int *value;
    int *limit;
    Page *targetPage;
};

struct ESPNowData
{
    bool stopStatus;
    bool startStatus;
    bool resetStatus;
    int sec;
    int mili;
};

#endif