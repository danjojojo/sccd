#include "../include/pages/turn_off.h"

extern SettingsPage settingsPage;

LabelPageOptionsStruct turnOffOptions[] = {
    {"CONFIRM", nullptr},
    {"Exit", &settingsPage},
};

int turnOffOptionsCount = getOptionsCount(turnOffOptions);
int selectedTurnOffOption = 0;

TurnOffPage::TurnOffPage(Button &btn, PageManager &manager) : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void TurnOffPage::drawStatusBar()
{
    page.drawStatusBar();
}

void TurnOffPage::drawOptions()
{
    page.drawOptions(turnOffOptions, turnOffOptionsCount, selectedTurnOffOption, false);
}

void TurnOffPage::shutOffDisplay()
{
    delay(300);
    esp_sleep_enable_ext1_wakeup(BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);
    digitalWrite(DISPLAY_BACKLIT, LOW);
    esp_deep_sleep_start();
}

void TurnOffPage::drawButtons(){
    page.drawButtons("Select", "Confirm");
}

void TurnOffPage::enter()
{
    page.tftInit();
    drawStatusBar();
    drawOptions();
    drawButtons();
}

void TurnOffPage::exit()
{
}

void TurnOffPage::handleButtonPress(){
    ButtonType buttonType = button.getButtonPressed();

    switch(buttonType){
        case LEFT_ONCE:
            selectedTurnOffOption = (selectedTurnOffOption + 1) % turnOffOptionsCount;
            delay(300);
            drawOptions();
            break;
        case RIGHT_ONCE:
            if(turnOffOptions[selectedTurnOffOption].targetPage == nullptr){
                shutOffDisplay();
            } else {
                pageManager.setPage(turnOffOptions[selectedTurnOffOption].targetPage);
            }
            break;
        default:
            break;
    }
}