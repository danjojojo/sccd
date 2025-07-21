#ifndef MAKEREADY_H
#define MAKEREADY_H

#include <Arduino.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/settings.h"
#include "../pages/timer.h"

class MakeReadyPage : public Page
{

private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    PageTemplate page;

public:
    MakeReadyPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
};

#endif