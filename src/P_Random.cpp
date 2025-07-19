#include "P_Random.h"

extern SettingsPage settingsPage;

LabelValuePageOptionsStruct randomOptions[] = {
    {"Random On", "RANDOM_ON", nullptr},
    {"Random Off", "RANDOM_OFF", nullptr},
    {"Back to Settings", nullptr, &settingsPage}};

int selectedRandomOption = 0;
int randomOptionsCount = getOptionsCount(randomOptions);

RandomPage::RandomPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void RandomPage::drawOptions()
{
    page.drawOptions(randomOptions, randomOptionsCount, selectedRandomOption, CURRENT_RANDOM_START);
}

void RandomPage::drawStatusBar()
{
    page.drawStatusBar();
}

void RandomPage::enter()
{
    page.tftInit();
    drawStatusBar();
    drawOptions();
    page.drawButtons("Select", "Confirm");
}

void RandomPage::exit()
{
    Serial.println("Exit Set Random Page");
}

void RandomPage::changeRandomValue(String value)
{
    if (!value)
    {
        return;
    }

    randomPreferences.begin("random", false);
    randomPreferences.putString("randomValue", value);
    randomPreferences.end();
}

void RandomPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        selectedRandomOption = (selectedRandomOption + 1) % randomOptionsCount;
        delay(300);
        drawOptions();
        break;
    case RIGHT_ONCE:
        if (randomOptions[selectedRandomOption].targetPage != nullptr)
        {
            pageManager.setPage(randomOptions[selectedRandomOption].targetPage);
        }
        else
        {
            changeRandomValue(randomOptions[selectedRandomOption].value);
            pageManager.setPage(&settingsPage);
        }
        selectedRandomOption = 0;
        break;
    default:
        break;
    }
}