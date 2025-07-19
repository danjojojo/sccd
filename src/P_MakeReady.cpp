#include "P_MakeReady.h"

extern SettingsPage settingsPage;
extern TimerPage timerPage;

MakeReadyPage::MakeReadyPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
    tft.setRotation(DISPLAY_ROTATION);
    tft.fillScreen(TFT_RED);
}

void MakeReadyPage::drawStatusBar()
{
    page.drawStatusBar();
}

void MakeReadyPage::enter()
{
    page.tftInit();
    page.drawTitle("Make Ready!");
    page.drawButtons(RIGHT, "Start");
    drawStatusBar();
}

void MakeReadyPage::exit()
{
    Serial.println("Exit Make Ready Page");
}

void MakeReadyPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_HOLD_2_SECONDS:
        pageManager.setPage(&settingsPage);
        break;
    case RIGHT_ONCE:
        pageManager.setPage(&timerPage);
        break;
    default:
        break;
    }
}