#include "P_EditAfterMatch.h"

extern TimerPage timerPage;

bool onEAMClick = false;
bool onEAMStartCountdown = false;
String eamOptionName = "Charlie";
unsigned long lastEAMInteractionTime = 0;

uint16_t selectedEAMOptionFontColor = ED_COLOR;

LabelIntValueLimitPageOptionsStruct eamOptionsPorB[] = {
    {"Charlie", &CHARLIE_NUM, &BOARDS_LIMIT, nullptr},
    {"Delta", &DELTA_NUM, &BOARDS_LIMIT, nullptr},
    {"Missed", &MISSED_NUM, &MISSED_LIMIT, nullptr},
    {"Back to Timer", nullptr, nullptr, &timerPage}};

LabelIntValueLimitPageOptionsStruct eamOptionsPOnly[] = {
    {"Missed", &MISSED_NUM, &MISSED_LIMIT, nullptr},
    {"Back to Timer", nullptr, nullptr, &timerPage}};

LabelIntValueLimitPageOptionsStruct *eamOptions;
int editAfterMatchOptionsCount;
int selectedEditAfterMatchOption = 0;

EditAfterMatchPage::EditAfterMatchPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void EditAfterMatchPage::drawOptions()
{
    page.drawOptions(eamOptions, editAfterMatchOptionsCount, selectedEditAfterMatchOption, selectedEAMOptionFontColor, eamOptionName, onEAMClick);
}

void EditAfterMatchPage::drawButtons()
{
    page.drawButtons("Select", "Confirm", onEAMClick);
}

void EditAfterMatchPage::adjustValue(EAMOperation op)
{

    auto &EAMOption = eamOptions[selectedEditAfterMatchOption];

    if (EAMOption.value == nullptr || EAMOption.limit == nullptr)
        return;

    switch (op)
    {
    case EAM_INCREASE:
        Serial.println("Increasing");
        (*EAMOption.value) += 1;
        if (*EAMOption.value > *EAMOption.limit)
        {
            *EAMOption.value = 0;
        }
        delay(300);
        break;
    case EAM_DECREASE:
        Serial.println("Decreasing");
        (*EAMOption.value) -= 1;
        if (*EAMOption.value == -1)
        {
            *EAMOption.value = *EAMOption.limit;
        }
        delay(300);
        break;
    default:
        break;
    }

    tft.fillRect(tft.width() - 30, listOptionsPadding(selectedEditAfterMatchOption) - 10, 30, 16, BG_COLOR);
    drawOptions();
}

void EditAfterMatchPage::flicker(int milliseconds)
{
    int interval = 500;
    while (milliseconds > 0)
    {
        selectedEAMOptionFontColor = ED_COLOR;
        delay(interval);
        drawOptions();
        selectedEAMOptionFontColor = TFT_DARKGREY;
        delay(interval);
        drawOptions();
        selectedEAMOptionFontColor = ED_COLOR;
        milliseconds -= interval * 2;
    }
}

void EditAfterMatchPage::storePBValue(const char *key, const int32_t *value)
{
    if (key == nullptr)
        return;

    eamPreferences.begin("eam", false);
    eamPreferences.putInt(key, *value);
    eamPreferences.end();
}

void EditAfterMatchPage::onEditTimeout()
{
    flicker(1000);
    lastEAMInteractionTime = 0;
    storePBValue(eamOptions[selectedEditAfterMatchOption].label, eamOptions[selectedEditAfterMatchOption].value);
    onEAMClick = false;
    drawOptions();
    drawButtons();
}

void EditAfterMatchPage::drawStatusBar()
{
    page.drawStatusBar();
}

void EditAfterMatchPage::enter()
{

    if (PLATES_NUM > 0 && BOARDS_NUM > 0)
    {
        eamOptions = eamOptionsPorB;
        editAfterMatchOptionsCount = getOptionsCount(eamOptionsPorB);
    }
    else if (PLATES_NUM > 0 && BOARDS_NUM == 0)
    {
        eamOptions = eamOptionsPOnly;
        editAfterMatchOptionsCount = getOptionsCount(eamOptionsPOnly);
    }

    page.tftInit();
    drawStatusBar();
    drawOptions();
    drawButtons();
}

void EditAfterMatchPage::exit()
{
    Serial.println("Exiting Settings page");
}

void EditAfterMatchPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        if (!onEAMClick)
        {
            selectedEditAfterMatchOption = (selectedEditAfterMatchOption + 1) % editAfterMatchOptionsCount;
            delay(300);
            drawOptions();
            drawButtons();
        }
        else
        {
            adjustValue(EAM_DECREASE);
            lastEAMInteractionTime = millis();
        }
        break;
    case RIGHT_ONCE:
        if (!onEAMClick)
        {
            if (eamOptions[selectedEditAfterMatchOption].targetPage != nullptr)
            {
                pageManager.setPage(eamOptions[selectedEditAfterMatchOption].targetPage);
            }
            else
            {
                onEAMClick = true;
                eamOptionName = eamOptions[selectedEditAfterMatchOption].label;
                delay(300);
                drawOptions();
                drawButtons();
            }
        }
        else
        {
            adjustValue(EAM_INCREASE);
            lastEAMInteractionTime = millis();
        }
        break;
    default:
        break;
    }

    if (onEAMClick && lastEAMInteractionTime > 0 && millis() - lastEAMInteractionTime > 3000)
    {
        onEditTimeout();
    }
}
