#include "../include/pages/timer.h"

extern MakeReadyPage makeReadyPage;
extern EditAfterMatchPage editAfterMatchPage;

static unsigned long startTime = millis();
static int lastSeconds = -1;
static int lastMilliseconds = -1;
int seconds = 0;
int milliseconds = 0;
String finishedTime;
String finishedSeconds;
String finishedMilliseconds;
String hitFactor = "N/A";

char elapsedTime[16];
char elapsedSeconds[4];
char elapsedMilliseconds[4];

TimerPage::TimerPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
    spr.createSprite(240, 135);
}

void TimerPage::drawStatusBar()
{
    page.drawStatusBar();
}

void TimerPage::randomStart()
{
    startTime = millis();
    int standByTime = random(3000, 6001);

    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    tft.drawString("STAND BY", tft.width() / 2, (tft.height() / 2) - 30);
    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(&Vipnagorgialla_Rg24pt7b);
    // tft.drawNumber(standByTime / 1000, tft.width() / 2, (tft.height() / 2) - 10);
    tft.drawNumber(standByTime / 1000, tft.width() / 2, (tft.height() / 2) + 10);

    while (millis() - startTime < standByTime)
    {
        int countdownTime = standByTime - (millis() - startTime);

        // tft.fillRect(0, (tft.height() / 2) - 10, tft.width(), 50, BG_COLOR);
        tft.fillRect(0, (tft.height() / 2) - 5, tft.width(), 50, BG_COLOR);
        tft.setTextDatum(MC_DATUM);
        tft.drawNumber(countdownTime / 1000, tft.width() / 2, (tft.height() / 2) + 10);
        delay(1000);
    }

    tft.fillRect(0, 20, tft.width(), 150, BG_COLOR);
    RANDOM_STARTED = true;
}

void TimerPage::playBuzzer(int times, int interval)
{
    for (int i = 0; i < times; i++)
    {
        tone(BUZZER_PIN, 2500);
        delay(interval);
        noTone(BUZZER_PIN);
        delay(200);
    }
    BUZZER_PLAYED = true;
}

void TimerPage::startTimer()
{

    if (!TIMER_RUNNING)
        return;

    unsigned long elapsed = millis() - startTime;
    seconds = elapsed / 1000;
    milliseconds = (elapsed % 1000) / 10;

    if (seconds != lastSeconds || milliseconds != lastMilliseconds)
    {
        lastSeconds = seconds;
        lastMilliseconds = milliseconds;

        sprintf(elapsedTime, "%02d.%02d", seconds, milliseconds);
        sprintf(elapsedSeconds, "%02d", seconds);
        sprintf(elapsedMilliseconds, ".%02d", milliseconds);

        finishedTime = elapsedTime;
        finishedSeconds = elapsedSeconds;
        finishedMilliseconds = elapsedMilliseconds;

        spr.setTextDatum(MC_DATUM);
        spr.fillRect(0, 0, tft.width(), 210, BG_COLOR);
        
        spr.setFreeFont(&ChakraPetch_Regular8pt7b);
        spr.setTextColor(FG_COLOR, BG_COLOR);
        spr.drawString("RUNNING", tft.width() / 2, (tft.height() / 2 ) - 55);

        spr.setTextColor(FG_COLOR, BG_COLOR);
        spr.setTextDatum(MR_DATUM);
        spr.setFreeFont(&Vipnagorgialla_Rg24pt7b);
        // spr.drawString(finishedSeconds, tft.width() / 2, tft.height() / 2 - 40);
        spr.drawString(finishedSeconds, (tft.width() / 2) - 5, (tft.height() / 2) - 20);

        spr.setTextColor(TFT_DARKGREY, BG_COLOR);
        spr.setTextDatum(ML_DATUM);
        spr.setFreeFont(&Vipnagorgialla_Rg24pt7b);
        // spr.drawString(finishedMilliseconds, tft.width() / 2, tft.height() / 2);
        spr.drawString(finishedMilliseconds, tft.width() / 2, (tft.height() / 2) - 20);
        spr.pushSprite(0,20);
    }
}

void TimerPage::computeHitFactor()
{
    int totalMatchPoints = (PLATES_NUM * 5) + ((BOARDS_NUM * 2) * 5);
    int afterMatchPoints = (CHARLIE_PTS * CHARLIE_NUM) + (DELTA_PTS * DELTA_NUM) + (MISSED_PTS * MISSED_NUM);

    float timeResult = seconds + (milliseconds / 100.0f);
    float hitFactorResult = (totalMatchPoints - afterMatchPoints) / timeResult;
    hitFactor = String(hitFactorResult);

    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    tft.setTextColor(TFT_DARKGREY, BG_COLOR);
    tft.drawString("TIME", 10, (tft.height() / 2) - 30);

    tft.setTextDatum(MR_DATUM);
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setFreeFont(&Vipnagorgialla_Rg24pt7b);
    tft.drawString(finishedTime, tft.width() - 10, (tft.height() / 2) - 30);

    tft.setTextDatum(ML_DATUM);
    tft.setFreeFont(&ChakraPetch_Regular8pt7b);
    tft.setTextColor(TFT_DARKGREY, BG_COLOR);
    tft.drawString("HIT FACTOR", 10, tft.height() / 2 + 20);

    tft.setTextDatum(MR_DATUM);
    tft.setTextColor(FG_COLOR, BG_COLOR);
    tft.setFreeFont(&Vipnagorgialla_Rg13pt7b);
    tft.drawFloat(hitFactorResult, 4, tft.width() - 10, tft.height() / 2 + 20);
}

void TimerPage::stopTimer()
{
    tft.fillScreen(BG_COLOR);
    Serial.println("Stop Timer");
    drawStatusBar();
    TIMER_RUNNING = false;

    if (PLATES_NUM != 0 || BOARDS_NUM != 0)
    {
        computeHitFactor();
        page.drawButtons("EDIT", "RESET");
    }
    else if (PLATES_NUM == 0 && BOARDS_NUM == 0)
    {
        hitFactor = "N/A";

        tft.setTextDatum(MC_DATUM);
        tft.setFreeFont(&ChakraPetch_Regular8pt7b);
        tft.setTextColor(TFT_DARKGREY, BG_COLOR);
        tft.drawString("TIME", tft.width() / 2, (tft.height() / 2) - 35);

        tft.setTextColor(FG_COLOR, BG_COLOR);
        tft.setFreeFont(&Vipnagorgialla_Rg24pt7b);
        tft.drawString(finishedTime, tft.width() / 2, (tft.height() / 2));

        page.drawButtons(RIGHT, "RESET");
    }
}

void TimerPage::resetTimer()
{
    resetEditAfterMatchBoards();
    TIMER_RUNNING = true;
    startTime = millis();
    lastSeconds = -1;
    lastMilliseconds = -1;
    seconds = 0;
    milliseconds = 0;
}

void TimerPage::saveTime()
{
    timerPreferences.begin("timerLogs", false);

    String timerValue = "T: " + finishedSeconds + finishedMilliseconds + " | " + "HF: " + hitFactor;

    // if TIMER_LOG_NUM >= MAX_LOGS meaning that our log has reached the max logs count
    if (TIMER_LOG_NUM >= MAX_LOGS)
    {
        // Shift the logs backward
        for (int i = 1; i < MAX_LOGS; i++)
        {
            char fromKey[20], toKey[20];
            sprintf(fromKey, "log_%d", i);
            sprintf(toKey, "log_%d", i - 1);

            String fromKeyValue = timerPreferences.getString(fromKey, "");
            timerPreferences.putString(toKey, fromKeyValue);
        }
        // Save the latest log on MAX_LOGS - 1 because TIMER_LOGS starts at 0 and ends at MAX_LOGS - 1
        char latestKey[20];
        sprintf(latestKey, "log_%d", MAX_LOGS - 1);
        timerPreferences.putString(latestKey, timerValue);

        // TIMER_LOG_NUM will be MAX_LOGS
        TIMER_LOG_NUM = MAX_LOGS;
        timerPreferences.putInt("logNum", TIMER_LOG_NUM);
    }
    else
    {
        char latestKey[20];
        sprintf(latestKey, "log_%d", TIMER_LOG_NUM);
        timerPreferences.putString(latestKey, timerValue);

        TIMER_LOG_NUM++;
        timerPreferences.putInt("logNum", TIMER_LOG_NUM);
    }
    RANDOM_STARTED = false;
    BUZZER_PLAYED = false;
    timerPreferences.end();
}

void TimerPage::enter()
{
    page.tftInit();
    drawStatusBar();

    if (RANDOM_START && !RANDOM_STARTED)
        randomStart();

    if (!BUZZER_PLAYED)
        playBuzzer(1, 500);

    // loop() will run because it was set in main.ino that if currentPage == timerPage, then the loop() function will be looped

    if (!TIMER_RUNNING)
    {
        stopTimer();
    }
    else
    {
        resetTimer();
    }
}

void TimerPage::exit()
{
    Serial.println("Exit Timer Page");
}

void TimerPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:
        if (TIMER_RUNNING)
        {
            BUZZER_PLAYED = false;
            RANDOM_STARTED = false;
            pageManager.setPage(&makeReadyPage);
        }
        else if (!TIMER_RUNNING && (PLATES_NUM != 0 || BOARDS_NUM != 0))
        {
            pageManager.setPage(&editAfterMatchPage);
        }
        break;
    case RIGHT_ONCE:
        if (TIMER_RUNNING)
        {
            stopTimer();
            playBuzzer(2, 200);
        }
        
        // if (!TIMER_RUNNING)
        else
        {
            resetTimer();
            saveTime();
            pageManager.setPage(&makeReadyPage);
        }
        break;
    default:
        break;
    }

    if (RECEIVED_DATA.stopStatus && TIMER_RUNNING)
    {
        stopTimer();
        playBuzzer(2, 200);
    }
}