#ifndef SETTHEME_H
#define SETTHEME_H

#include <Arduino.h>
#include <Preferences.h>

#include "C_Button.h"
#include "C_Page.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

#include "P_MakeReady.h"
#include "P_Settings.h"

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