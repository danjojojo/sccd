#include "../include/pages/set_theme.h"

extern SettingsPage settingsPage;
extern MakeReadyPage makeReadyPage;

LabelValuePageOptionsStruct themeOptions[] = {
    {"Dark", "BLACK_WHITE", nullptr},
    {"Light", "WHITE_BLACK", nullptr},
    {"Back to Settings", nullptr, &settingsPage}};

int themeOptionsCount = getOptionsCount(themeOptions);
int selectedThemeOption = 0;

SetThemePage::SetThemePage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void SetThemePage::drawOptions()
{
    page.drawOptions(themeOptions, themeOptionsCount, selectedThemeOption, CURRENT_THEME);
}

void SetThemePage::drawStatusBar()
{
    page.drawStatusBar();
}

void SetThemePage::enter()
{
    page.tftInit();
    drawStatusBar();
    drawOptions();
    page.drawButtons("Select", "Confirm");
}

void SetThemePage::exit()
{
    Serial.println("Exit Set Theme Page");
}

void SetThemePage::changeTheme(String value)
{
    preferences.begin("themes", false);
    String currentThemeValue = preferences.getString("Theme", "BLACK_WHITE");
    if (value)
    {
        preferences.putString("Theme", value);
    }
    preferences.end();
}

void SetThemePage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        selectedThemeOption = (selectedThemeOption + 1) % themeOptionsCount;
        delay(300);
        drawOptions();
        break;
    case RIGHT_ONCE:
        if (themeOptions[selectedThemeOption].targetPage != nullptr)
        {
            pageManager.setPage(themeOptions[selectedThemeOption].targetPage);
        }
        else
        {
            changeTheme(themeOptions[selectedThemeOption].value);
            pageManager.setPage(&settingsPage);
        }
        selectedThemeOption = 0;
        break;
    default:
        break;
    }
}