#include "../include/pages/set_orientation.h"

extern SettingsPage settingsPage;

LabelValuePageOptionsStruct orientationOptions[] = {
    {"PORTRAIT 1", "P1", nullptr},
    {"PORTRAIT 2", "P2", nullptr},
    {"LANDSCAPE 1", "L1", nullptr},
    {"LANDSCAPE 2", "L2", nullptr},
    {"Exit", nullptr, &settingsPage}};

int orientationOptionsCount = getOptionsCount(orientationOptions);
int selectedOrientation = 0;

SetOrientationPage::SetOrientationPage(Button &btn, PageManager &manager) : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void SetOrientationPage::drawStatusBar()
{
    page.drawStatusBar();
}

void SetOrientationPage::drawOptions()
{
    page.drawOptions(orientationOptions, orientationOptionsCount, selectedOrientation, CURRENT_ORIENTATION);
}

void SetOrientationPage::changeOrientation(String value){
    if(!value){
        return;
    }

    ortPref.begin("orientations", false);
    ortPref.putString("orientation", value);
    ortPref.end();
}

void SetOrientationPage::enter()
{
    page.tftInit();
    drawOptions();
    page.drawButtons("Select", "Confirm");
}

void SetOrientationPage::exit()
{
    Serial.println("Exit this Orientation Page");
}

void SetOrientationPage::handleButtonPress()
{
    ButtonType buttonType = button.getButtonPressed();

    switch (buttonType)
    {
    case LEFT_ONCE:
        selectedOrientation = (selectedOrientation + 1) % orientationOptionsCount;
        delay(300);
        drawOptions();
        break;
    case RIGHT_ONCE:
        if (orientationOptions[selectedOrientation].value == nullptr)
        {
            pageManager.setPage(orientationOptions[selectedOrientation].targetPage);
        } else {
            changeOrientation(orientationOptions[selectedOrientation].value);
            pageManager.setPage(&settingsPage);
        }
        break;
    default:
        break;
    }
}