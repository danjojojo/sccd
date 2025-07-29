#ifndef SETORIENTATION_H
#define SETORIENTATION_H

#include <Arduino.h>

#include "../class/button.h"
#include "../class/page.h"
#include "../class/page_template.h"
#include "../core/page_manager.h"

#include "../pages/settings.h"

class SetOrientationPage : public Page {
    private:
        Button &button;
        PageManager &pageManager;
        TFT_eSPI tft = TFT_eSPI();
        PageTemplate page;
        Preferences ortPref;

    public:
        SetOrientationPage(Button &btn, PageManager &manager);
        void drawStatusBar();
        void drawOptions();
        void changeOrientation(String value);
        void enter();
        void exit();
        void handleButtonPress();
};


#endif