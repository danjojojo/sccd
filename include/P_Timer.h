#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Preferences.h>

#include "C_Button.h"
#include "C_Page.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

#include "P_EditAfterMatch.h"
#include "P_MakeReady.h"

class TimerPage : public Page
{

private:
    Button &button;
    PageManager &pageManager;
    TFT_eSPI tft = TFT_eSPI();
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