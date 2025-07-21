#include "../include/pages/timer.h"

extern MakeReadyPage makeReadyPage;
extern EditAfterMatchPage editAfterMatchPage;

static unsigned long startTime = 0;
static int lastSeconds = -1;
static int lastMilliseconds = -1;
int seconds = 0;
int milliseconds = 0;
String finishedTime;
String hitFactor = "N/A";

TimerPage::TimerPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void TimerPage::drawStatusBar()
{
    page.drawStatusBar();
}

void TimerPage::randomStart()
{
    unsigned long startTime = millis();
    int standByTime = random(3000, 6001);

    tft.setTextDatum(MC_DATUM);
    tft.drawString("Stand by", tft.width() / 2, (tft.height() / 2) - 25);
    tft.setTextDatum(MC_DATUM);
    tft.drawNumber(standByTime / 1000, tft.width() / 2, tft.height() / 2);

    while (millis() - startTime < standByTime)
    {
        int countdownTime = standByTime - (millis() - startTime);

        tft.fillRect(0, (tft.height() / 2) - 5, tft.width(), 50, BG_COLOR);
        tft.setTextDatum(MC_DATUM);
        tft.drawNumber(countdownTime / 1000, tft.width() / 2, tft.height() / 2);
        delay(1000);
    }

    tft.fillScreen(BG_COLOR);
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

        char elapsedTime[16];
        sprintf(elapsedTime, "%02d.%02d", seconds, milliseconds);
        finishedTime = elapsedTime;

        tft.setTextPadding(60);
        tft.fillRect(0, 80, tft.width(), 50, BG_COLOR);
        tft.setTextDatum(MC_DATUM);
        tft.drawString(elapsedTime, tft.width() / 2, tft.height() / 2);
    }
}

void TimerPage::computeHitFactor()
{
    int totalMatchPoints = (PLATES_NUM * 5) + ((BOARDS_NUM * 2) * 5);
    int afterMatchPoints = (CHARLIE_PTS * CHARLIE_NUM) + (DELTA_PTS * DELTA_NUM) + (MISSED_PTS * MISSED_NUM);

    float timeResult = seconds + (milliseconds / 100.0f);
    float hitFactorResult = (totalMatchPoints - afterMatchPoints) / timeResult;
    hitFactor = String(hitFactorResult);

    tft.setTextDatum(MC_DATUM);
    tft.drawString(finishedTime, tft.width() / 2, tft.height() / 2 - 20);
    tft.drawString("Hit Factor", tft.width() / 2, tft.height() / 2 + 20);
    tft.drawFloat(hitFactorResult, 5, tft.width() / 2, tft.height() / 2 + 40);
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
        page.drawButtons("Edit", "Reset");
    }
    else if (PLATES_NUM == 0 && BOARDS_NUM == 0)
    {
        hitFactor = "N/A";
        page.drawTitle(finishedTime);
        page.drawButtons(RIGHT, "Reset");
    }
}

void TimerPage::resetTimer()
{
    resetEditAfterMatchBoards();
    RECEIVED_DATA = {false, false, false, false};
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

    String timerValue = "T: " + finishedTime + " | " + "HF: " + hitFactor;

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
            pageManager.setPage(&makeReadyPage);
        }
        else if (!TIMER_RUNNING && (PLATES_NUM != 0 || BOARDS_NUM != 0))
        {
            pageManager.setPage(&editAfterMatchPage);
        }
        break;
    case RIGHT_ONCE:
        if (!TIMER_RUNNING)
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