#include "P_Settings.h"

extern PlateBoardManagerPage plateBoardManagerPage;
extern RandomPage randomPage;
extern SetThemePage setThemePage;
extern LogsPage logsPage;
extern MakeReadyPage makeReadyPage;

LabelPageOptionsStruct settingOptions[] = {
    {"Plates and Boards", &plateBoardManagerPage},
    {"Random Start", &randomPage},
    {"Timer Logs", &logsPage},
    {"Change Theme", &setThemePage},
    {"Exit to Main Menu", &makeReadyPage},
    {"Turn Off", nullptr}};

int settingOptionsCount = getOptionsCount(settingOptions);
int selectedSettingOption = 0;

SettingsPage::SettingsPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void SettingsPage::drawOptions()
{
    page.drawOptions(settingOptions, settingOptionsCount, selectedSettingOption);
}

void SettingsPage::drawButtons()
{
    page.drawButtons("Select", "Confirm");
}

void SettingsPage::drawStatusBar()
{
    page.drawStatusBar();
}

void SettingsPage::enter()
{
    page.tftInit();
    drawStatusBar();
    drawOptions();
    drawButtons();
}

void SettingsPage::exit()
{
    Serial.println("Exiting Settings page");
}

void SettingsPage::shutOffDisplay()
{
    delay(300);
    esp_sleep_enable_ext1_wakeup(BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);
    digitalWrite(DISPLAY_BACKLIT, LOW);
    esp_deep_sleep_start();
}

void SettingsPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        selectedSettingOption = (selectedSettingOption + 1) % settingOptionsCount;
        delay(300);
        drawOptions();
        break;
    case RIGHT_ONCE:
        if (settingOptions[selectedSettingOption].targetPage != nullptr)
        {
            pageManager.setPage(settingOptions[selectedSettingOption].targetPage);
        }
        else
        {
            shutOffDisplay();
        }
        selectedSettingOption = 0;
        break;
    default:
        break;
    }
}