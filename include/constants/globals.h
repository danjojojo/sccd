#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Pangodream_18650_CL.h>
#include <Preferences.h>
#include <TFT_eSPI.h>

#include "../class/connection.h"
#include "./structs.h"

// DISPLAY
extern int DISPLAY_ROTATION;

// THEME
extern uint16_t BG_COLOR;
extern uint16_t FG_COLOR;
extern uint16_t ED_COLOR;

// PLATES AND BOARDS
extern int32_t PLATES_NUM;
extern int32_t BOARDS_NUM;
extern int32_t PLATES_LIM;
extern int32_t BOARDS_LIM;

// EDIT AFTER MATCH
extern int32_t CHARLIE_NUM;
extern int32_t DELTA_NUM;
extern int32_t MISSED_NUM;
extern int32_t CHARLIE_PTS;
extern int32_t DELTA_PTS;
extern int32_t MISSED_PTS;
extern int32_t BOARDS_LIMIT;
extern int32_t MISSED_LIMIT;

// TIMER LOGS
extern int32_t TIMER_LOG_NUM;
extern const int MAX_LOGS;
extern String TIMER_LOGS[];

// TIMER
extern bool TIMER_RUNNING;
extern bool BUZZER_PLAYED;

// RANDOM START
extern bool RANDOM_START;
extern bool RANDOM_STARTED;

// FOR CURRENT OPTION
extern String CURRENT_THEME;
extern String CURRENT_RANDOM_START;

// TFT
extern TFT_eSPI tft;

// PREFERENCES
extern Preferences pref;

// BATTERY
extern Pangodream_18650_CL BL;
extern int SENSOR_VALUE;
extern float VOLTAGE;
extern String BATTERY_LEVEL;
// extern int BATTERY_LEVEL;

// INTERVALS FOR VOID LOOP IN MAIN.INO
extern unsigned long LAST_ACTION_TIME;
extern unsigned long INTERVAL;

// CONNECTION
extern Connection connect;
extern String CONNECTION_SIGNAL;
extern bool CONNECTED;
extern bool STOP_TIMER;
extern ESPNowData TOSUBMIT_DATA;
extern ESPNowData RECEIVED_DATA;

#endif