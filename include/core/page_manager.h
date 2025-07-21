#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include <Arduino.h>

#include "../class/page.h"
#include "../state/load_states.h"

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