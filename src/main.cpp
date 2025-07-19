// BASE
#include <Arduino.h>

// FOR BUTTON INTERACTION AND NAVIGATION
#include "C_Page.h"
#include "C_Button.h"
#include "C_PageManager.h"
#include "C_PageTemplate.h"

// MAIN PAGES
#include "P_Settings.h"
#include "P_MakeReady.h"
#include "P_Timer.h"

// SETTING OPTIONS
#include "P_PlateBoardManager.h"
#include "P_Random.h"
#include "P_SetTheme.h"
#include "P_EditAfterMatch.h"
#include "P_Logs.h"

// CONSTANTS
#include "H_Constants.h"

// LOAD STATES
#include "H_LoadStates.h"

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
