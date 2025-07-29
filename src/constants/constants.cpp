#include "../include/constants/constants.h"

// OBJECTS
TFT_eSPI tft = TFT_eSPI();
Preferences pref;
Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);
Connection connect;

// DISPLAY
int DISPLAY_ROTATION = 1; // 0,2 = Portrait, 1,3 = Landscape

// THEMES
uint16_t BG_COLOR = TFT_BLACK;
uint16_t FG_COLOR = TFT_WHITE;
uint16_t ED_COLOR = TFT_RED;

// PLATES AND BOARDS MANAGER
int32_t PLATES_NUM = 10;
int32_t BOARDS_NUM = 5;
int32_t PLATES_LIM = 25;
int32_t BOARDS_LIM = 25;

// EDIT AFTER MATCH
int32_t CHARLIE_NUM = 0;
int32_t DELTA_NUM = 0;
int32_t MISSED_NUM = 0;
int32_t CHARLIE_PTS = 3;
int32_t DELTA_PTS = 1;
int32_t MISSED_PTS = 10;
int32_t BOARDS_LIMIT = 5;
int32_t MISSED_LIMIT = 5;

// TIMER
bool TIMER_RUNNING = true;
bool BUZZER_PLAYED = false;

// TIMER_LOGS
int32_t TIMER_LOG_NUM = 0;
const int MAX_LOGS = 10;
String TIMER_LOGS[MAX_LOGS];

// RANDOM START
bool RANDOM_START = false;
bool RANDOM_STARTED = false;

// FOR OPTIONS TO ADD (using) IF CURRENT OPTION IS BEING USED
String CURRENT_THEME;
String CURRENT_RANDOM_START;

// BATTERY
int SENSOR_VALUE;
float VOLTAGE;
// String BATTERY_LEVEL;
int BATTERY_LEVEL;

// INTERVAL
unsigned long LAST_ACTION_TIME = 0;
unsigned long INTERVAL = 1000;

// CONNECTION
String CONNECTION_SIGNAL;
bool CONNECTED = false;
bool STOP_TIMER = false;
ESPNowData TOSUBMIT_DATA = {false, false, false, false};
ESPNowData RECEIVED_DATA = {false, false, false, false};

// DRAW OPTIONS
int PAGE_ITEMS_LIMIT = 4;
const int MAX_PAGES = 10;
int COLUMNS[MAX_PAGES];
int PAGES = 0;
int CURRENT_PAGE = 0;
int START_COUNT = 0;
int REFRESH_HEIGHT = 0;

// ORIENTATION
String CURRENT_ORIENTATION;