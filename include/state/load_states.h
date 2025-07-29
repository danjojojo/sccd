#ifndef LOADSTATES_H
#define LOADSTATES_H

#include <Arduino.h>

#include "../constants/constants.h"
#include "../utils/utils.h"

void loadPinmode();
void loadThemeColors();
void loadPlatesAndBoards();
void loadEditAfterMatchBoards();
void resetEditAfterMatchBoards();
void loadTimerLogs();
void loadRandomValue();
void loadBattery();
void loadConnection();
void loadOrientation();
void requestConnection();
void loadReceivedData();
void resetReceivedData();

#endif