#ifndef SETTHEME_H
#define SETTHEME_H

#include <Arduino.h>
#include <Preferences.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/make_ready.h"
#include "../pages/settings.h"

class SetThemePage : public Page
{
private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    Preferences preferences;
    PageTemplate page;

public:
    SetThemePage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawOptions();
    void changeTheme(String value);
};

#endif