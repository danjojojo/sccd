#ifndef TURNOFF_H
#define TURNOFF_H

#include <Arduino.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/settings.h"

class TurnOffPage : public Page
{
private:
    Button &button;
    PageManager &pageManager;
    PageTemplate page;
    TFT_eSPI tft = TFT_eSPI();

public:
    TurnOffPage(Button &btn, PageManager &manager);
    void enter();
    void exit();
    void handleButtonPress();
    void drawStatusBar();
    void drawOptions();
    void drawButtons();
    void shutOffDisplay();
};

#endif