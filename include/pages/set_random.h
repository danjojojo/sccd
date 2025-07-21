#ifndef SETRANDOM_H
#define SETRANDOM_H

#include <Arduino.h>
#include <Preferences.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/settings.h"

class RandomPage : public Page
{
private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    Preferences randomPreferences;
    PageTemplate page;

public:
    RandomPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawOptions();
    void changeRandomValue(String value);
};

#endif