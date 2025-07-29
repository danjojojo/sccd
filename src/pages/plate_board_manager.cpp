#include "../include/pages/plate_board_manager.h"

extern SettingsPage settingsPage;

bool onPBClick = false;
bool onStartCountdown = false;
String optionName = "Plates";
unsigned long lastInteractionTime = 0;

uint16_t selectedOptionFontColor = ED_COLOR;

LabelIntValueLimitPageOptionsStruct plateBoardManagerOptions[] = {
    {"P", &PLATES_NUM, &PLATES_LIM, nullptr},
    {"B", &BOARDS_NUM, &BOARDS_LIM, nullptr},
    {"Exit", nullptr, nullptr, &settingsPage}};

int plateBoardManagerOptionsCount = getOptionsCount(plateBoardManagerOptions);
int selectedPlateBoardManagerOption = 0;

PlateBoardManagerPage::PlateBoardManagerPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void PlateBoardManagerPage::drawOptions()
{
    page.drawOptions(plateBoardManagerOptions, plateBoardManagerOptionsCount, selectedPlateBoardManagerOption, selectedOptionFontColor, optionName, onPBClick);
}

void PlateBoardManagerPage::drawButtons()
{
    page.drawButtons("Select", "Confirm", onPBClick);
}

void PlateBoardManagerPage::adjustValue(PBOperation op)
{

    auto &PBOption = plateBoardManagerOptions[selectedPlateBoardManagerOption];

    if (PBOption.value == nullptr || PBOption.limit == nullptr)
        return;

    switch (op)
    {
    case PB_INCREASE:
        (*PBOption.value) += 1;
        if (*PBOption.value > *PBOption.limit)
        {
            *PBOption.value = 0;
        }
        delay(300);
        break;
    case PB_DECREASE:
        (*PBOption.value) -= 1;
        if (*PBOption.value == -1)
        {
            *PBOption.value = *PBOption.limit;
        }
        delay(300);
        break;
    default:
        break;
    }

    tft.fillRect(tft.width() - 30, listOptionsPadding(selectedPlateBoardManagerOption) - 10, 30, 16, BG_COLOR);
    drawOptions();
}

void PlateBoardManagerPage::flicker(int milliseconds)
{
    int interval = 500;
    while (milliseconds > 0)
    {
        selectedOptionFontColor = ED_COLOR;
        delay(interval);
        drawOptions();
        selectedOptionFontColor = TFT_DARKGREY;
        delay(interval);
        drawOptions();
        selectedOptionFontColor = ED_COLOR;
        milliseconds -= interval * 2;
    }
}

void PlateBoardManagerPage::storePBValue(const char *key, const int32_t *value)
{
    if (key == nullptr)
        return;

    pbPreferences.begin("pb", false);
    pbPreferences.putInt(key, *value);
    pbPreferences.end();
}

void PlateBoardManagerPage::onEditTimeout()
{
    flicker(500);
    lastInteractionTime = 0;
    storePBValue(plateBoardManagerOptions[selectedPlateBoardManagerOption].label, plateBoardManagerOptions[selectedPlateBoardManagerOption].value);
    onPBClick = false;
    drawOptions();
    drawButtons();
}

void PlateBoardManagerPage::drawStatusBar()
{
    page.drawStatusBar();
}

void PlateBoardManagerPage::enter()
{
    page.tftInit();
    drawStatusBar();
    drawOptions();
    drawButtons();
}

void PlateBoardManagerPage::exit()
{
    Serial.println("Exiting Settings page");
}

void PlateBoardManagerPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        if (!onPBClick)
        {
            selectedPlateBoardManagerOption = (selectedPlateBoardManagerOption + 1) % plateBoardManagerOptionsCount;
            delay(300);
            drawOptions();
            drawButtons();
        }
        else
        {
            adjustValue(PB_DECREASE);
            lastInteractionTime = millis();
        }
        break;
    case RIGHT_ONCE:
        if (!onPBClick)
        {
            if (plateBoardManagerOptions[selectedPlateBoardManagerOption].targetPage != nullptr)
            {
                pageManager.setPage(plateBoardManagerOptions[selectedPlateBoardManagerOption].targetPage);
            }
            else
            {
                onPBClick = true;
                optionName = plateBoardManagerOptions[selectedPlateBoardManagerOption].label;
                delay(300);
                drawOptions();
                drawButtons();
            }
        }
        else
        {
            adjustValue(PB_INCREASE);
            lastInteractionTime = millis();
        }
        break;
    default:
        break;
    }

    if (onPBClick && lastInteractionTime > 0 && millis() - lastInteractionTime > 3000)
    {
        onEditTimeout();
    }
}
