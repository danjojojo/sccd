#include "../include/pages/settings.h"

extern PlateBoardManagerPage plateBoardManagerPage;
extern RandomPage randomPage;
extern SetOrientationPage setOrientationPage;
extern SetThemePage setThemePage;
extern LogsPage logsPage;
extern MakeReadyPage makeReadyPage;
extern TurnOffPage turnOffPage;

LabelPageOptionsStruct settingOptions[] = {
    {"PB MANAGER", &plateBoardManagerPage},
    {"RANDOM START", &randomPage},
    {"TIMER LOGS", &logsPage},
    // {"ORIENTATION", &setOrientationPage},
    {"THEMES", &setThemePage},
    {"MAIN MENU", &makeReadyPage},
    {"TURN OFF", nullptr},
    // {"TURN OFF", &turnOffPage},
};

int settingOptionsCount = getOptionsCount(settingOptions);
int selectedSettingOption = 0;
int settingsCurrentPage = 0;

SettingsPage::SettingsPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void SettingsPage::drawOptions()
{
    page.drawPaginatedOptions(settingOptions, settingOptionsCount, selectedSettingOption, true);
}

void SettingsPage::drawButtons()
{
    page.drawButtons("Select", "Confirm");
}

void SettingsPage::drawStatusBar()
{
    page.drawStatusBar();
}

void SettingsPage::shutOffDisplay()
{
    delay(300);
    esp_sleep_enable_ext1_wakeup(BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);
    digitalWrite(DISPLAY_BACKLIT, LOW);
    esp_deep_sleep_start();
}

void SettingsPage::enter()
{
    getItemsPerPage(settingOptionsCount);
    page.tftInit();
    drawStatusBar();
    drawOptions();
    drawButtons();
}

void SettingsPage::exit()
{
    Serial.println("Exiting Settings page");
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
        if (settingOptions[selectedSettingOption].targetPage == nullptr)
        {
            shutOffDisplay();
        }
        else
        {
            pageManager.setPage(settingOptions[selectedSettingOption].targetPage);
        }
        selectedSettingOption = 0;
        break;
    default:
        break;
    }
}