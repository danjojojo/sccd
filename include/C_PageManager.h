#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <Arduino.h>

#include "C_Page.h"
#include "H_LoadStates.h"

class PageManager
{
private:
    Page *currentPage;

public:
    PageManager();
    void setPage(Page *newPage);
    Page *getCurrentPage();
    void handleButtonPress();
};

#endif