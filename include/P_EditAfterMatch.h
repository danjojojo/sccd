#ifndef EDITAFTERMATCH_H
#define EDITAFTERMATCH_H

#include <Arduino.h>
#include <Preferences.h>

#include "C_Button.h"
#include "C_Page.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

#include "P_Timer.h"

class EditAfterMatchPage : public Page
{
private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    Preferences eamPreferences;
    PageTemplate page;

public:
    EditAfterMatchPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawOptions();
    void drawButtons();
    void flicker(int milliseconds);
    void storePBValue(const char *key, const int32_t *value);
    void onEditTimeout();
    void adjustValue(EAMOperation op);
};

#endif