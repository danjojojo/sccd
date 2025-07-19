#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

#include "C_Button.h"
#include "C_Page.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

#include "P_Logs.h"
#include "P_MakeReady.h"
#include "P_PlateBoardManager.h"
#include "P_Random.h"
#include "P_SetTheme.h"

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