#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/logs.h"
#include "../pages/make_ready.h"
#include "../pages/plate_board_manager.h"
#include "../pages/set_random.h"
#include "../pages/set_theme.h"

class SettingsPage : public Page
{

private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    PageTemplate page;

public:
    SettingsPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawButtons();
    void drawOptions();
    void shutOffDisplay();
};

#endif