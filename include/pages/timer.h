#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Preferences.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/edit_after_match.h"
#include "../pages/make_ready.h"

class TimerPage : public Page
{

private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
    TFT_eSprite spr = TFT_eSprite(&tft);
    Preferences timerPreferences;
    PageTemplate page;

public:
    TimerPage(Button &btn, PageManager &manager);
    void enter() override;
    void exit() override;
    void handleButtonPress() override;
    void drawStatusBar();
    void randomStart();
    void startTimer();
    void stopTimer();
    void playBuzzer(int times, int interval);
    void computeHitFactor();
    void saveTime();
    void resetTimer();
};

#endif