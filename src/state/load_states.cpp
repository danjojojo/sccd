#include "../include/state/load_states.h"

void loadPinmode()
{
    pinMode(DISPLAY_BACKLIT, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loadThemeColors()
{
    pref.begin("themes", true);
    CURRENT_THEME = pref.getString("Theme", "BLACK_WHITE");
    Theme currentTheme = getThemeFromString(CURRENT_THEME);
    switch (currentTheme)
    {
    case THEME_BLACK_WHITE:
        BG_COLOR = TFT_BLACK;
        FG_COLOR = TFT_WHITE;
        ED_COLOR = TFT_RED;
        break;
    case THEME_WHITE_BLACK:
        BG_COLOR = TFT_WHITE;
        FG_COLOR = TFT_BLACK;
        ED_COLOR = TFT_RED;
        break;
    default:
        BG_COLOR = TFT_BLACK;
        FG_COLOR = TFT_WHITE;
        ED_COLOR = TFT_RED;
        break;
    }
    pref.end();
}

void loadPlatesAndBoards()
{
    pref.begin("pb", true);
    PLATES_NUM = pref.getInt("Plates", 10);
    BOARDS_NUM = pref.getInt("Boards", 5);
    pref.end();
}

void loadEditAfterMatchBoards()
{
    pref.begin("eam", true);
    CHARLIE_NUM = pref.getInt("Charlie", 0);
    DELTA_NUM = pref.getInt("Delta", 0);
    MISSED_NUM = pref.getInt("Missed", 0);
    BOARDS_LIMIT = BOARDS_NUM * 2;
    MISSED_LIMIT = BOARDS_LIMIT + PLATES_NUM;
    pref.end();
}

void resetEditAfterMatchBoards()
{
    pref.begin("eam", false);
    pref.putInt("Charlie", 0);
    pref.putInt("Delta", 0);
    pref.putInt("Missed", 0);
    pref.end();
}

void loadTimerLogs()
{
    pref.begin("timerLogs", true);
    TIMER_LOG_NUM = pref.getInt("logNum", 0);
    int NUM = 0;
    while (NUM < TIMER_LOG_NUM)
    {
        char LOG_KEY[20];
        sprintf(LOG_KEY, "log_%d", NUM);
        String LOG_VALUE = pref.getString(LOG_KEY, "Log ends here");
        TIMER_LOGS[NUM] = LOG_VALUE;
        NUM++;
    }
    pref.end();
}

void loadRandomValue()
{
    pref.begin("random", true);
    String randValue = pref.getString("randomValue", "RANDOM_ON");
    CURRENT_RANDOM_START = randValue;
    RANDOM_START = CURRENT_RANDOM_START == "RANDOM_ON" ? true : false;
    pref.end();
}

void loadBattery()
{
    SENSOR_VALUE = analogRead(ADC_PIN);
    VOLTAGE = BL.getBatteryVolts();
    BatteryLevels currentBatteryLevel = getBatteryLevel(VOLTAGE);
    switch (currentBatteryLevel)
    {
    case EMPTY:
        BATTERY_LEVEL = String(VOLTAGE) + " ----";
        break;
    case ONE_BAR:
        BATTERY_LEVEL = String(VOLTAGE) + " I---";
        break;
    case TWO_BARS:
        BATTERY_LEVEL = String(VOLTAGE) + " II--";
        break;
    case THREE_BARS:
        BATTERY_LEVEL = String(VOLTAGE) + " III-";
        break;
    case FOUR_BARS:
        BATTERY_LEVEL = String(VOLTAGE) + " IIII";
        break;
    case FULL:
        BATTERY_LEVEL = String(VOLTAGE) + " Full";
        break;
    case CHARGING:
        BATTERY_LEVEL = String(VOLTAGE) + " Chrg";
        break;
    default:
        break;
    }
}

void loadConnection()
{
    connect.espNowInit();
    connect.setPeer(STOP_PLATE_MAC_ADDRESS);
}

void requestConnection()
{
    TOSUBMIT_DATA.startStatus = true;
    CONNECTED = connect.sendData(STOP_PLATE_MAC_ADDRESS, TOSUBMIT_DATA);
    CONNECTION_SIGNAL = CONNECTED ? "C" : "X";
}

void loadReceivedData()
{
    RECEIVED_DATA = connect.getReceivedData();
}

void resetReceivedData()
{
    connect.resetData();
}