// BASE
#include <Arduino.h>

// FOR BUTTON INTERACTION AND NAVIGATION
#include "../include/class/button.h"
#include "../include/class/page.h"
#include "../include/class/page_template.h"
#include "../include/core/page_manager.h"

// MAIN PAGES
#include "../include/pages/settings.h"
#include "../include/pages/make_ready.h"
#include "../include/pages/timer.h"

// SETTING OPTIONS
#include "../include/pages/logs.h"
#include "../include/pages/plate_board_manager.h"
#include "../include/pages/set_random.h"
#include "../include/pages/set_theme.h"
#include "../include/pages/edit_after_match.h"

// CONSTANTS
#include "../include/constants/constants.h"

// LOAD STATES
#include "../include/state/load_states.h"

Button btn(LEFT_BUTTON, RIGHT_BUTTON);
PageManager pageManager;

PageTemplate page(tft);

SettingsPage settingsPage(btn, pageManager);
MakeReadyPage makeReadyPage(btn, pageManager);
TimerPage timerPage(btn, pageManager);

PlateBoardManagerPage plateBoardManagerPage(btn, pageManager);
LogsPage logsPage(btn, pageManager);
RandomPage randomPage(btn, pageManager);
SetThemePage setThemePage(btn, pageManager);
EditAfterMatchPage editAfterMatchPage(btn, pageManager);

void setup()
{
  Serial.begin(115200);
  pageManager.setPage(&makeReadyPage);
  loadPinmode();
  loadConnection();
}

void loop()
{
  Page *current = pageManager.getCurrentPage();
  bool isTimerPage = current == &timerPage;

  if (current)
  {
    current->handleButtonPress();
    loadBattery();

    if (millis() - LAST_ACTION_TIME >= INTERVAL)
    {
      LAST_ACTION_TIME = millis();
      requestConnection();
      current->drawStatusBar();
    }
  }

  if (pageManager.getCurrentPage() == &timerPage)
  {
    timerPage.startTimer();
    loadReceivedData();
  }
}
