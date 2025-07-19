#ifndef LOADSTATES_H
#define LOADSTATES_H

#include <Arduino.h>

#include "H_Constants.h"
#include "H_Utils.h"

void loadPinmode();
void loadThemeColors();
void loadPlatesAndBoards();
void loadEditAfterMatchBoards();
void resetEditAfterMatchBoards();
void loadTimerLogs();
void loadRandomValue();
void loadBattery();
void loadConnection();
void requestConnection();
void loadReceivedData();
void resetReceivedData();

#endif