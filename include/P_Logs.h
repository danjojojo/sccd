#ifndef LOGS_H
#define LOGS_H

#include <Arduino.h>

#include "C_Button.h"
#include "C_Page.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

#include "P_Settings.h"

class LogsPage : public Page
{
private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    PageTemplate page;

public:
    LogsPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void drawLogs();
};

#endif