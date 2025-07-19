#ifndef STRUCTCONSTANTS_H
#define STRUCTCONSTANTS_H

#include "C_Page.h"

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