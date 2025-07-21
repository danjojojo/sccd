#ifndef PLATEBOARDMANAGER_H
#define PLATEBOARDMANAGER_H

#include <Arduino.h>
#include <Preferences.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/settings.h"

class PlateBoardManagerPage : public Page
{

private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    PageTemplate page;
    Preferences pbPreferences;

public:
    PlateBoardManagerPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawOptions();
    void drawButtons();
    void flicker(int milliseconds);
    void storePBValue(const char *key, const int32_t *value);
    void onEditTimeout();
    void adjustValue(PBOperation op);
};

#endif