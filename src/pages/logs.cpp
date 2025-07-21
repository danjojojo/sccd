#include "../include/pages/logs.h"

extern SettingsPage settingsPage;

int selectedLogNum = 0;
int logsCount = 0;

LogsPage::LogsPage(Button &btn, PageManager &manager)
    : button(btn), pageManager(manager), page(tft)
{
    tft.init();
}

void LogsPage::drawLogs()
{
    tft.fillRect(0, 100, tft.width(), 30, BG_COLOR);
    tft.setTextDatum(ML_DATUM);

    if (logsCount == 0)
    {
        tft.setTextColor(TFT_DARKGREY);
        tft.drawString("No logs here.", 5, listOptionsPadding(0));
        return;
    }

    int line = 0;
    for (int i = logsCount - 1; i >= 0; i--)
    {
        if (i == selectedLogNum)
        {
            tft.setTextColor(FG_COLOR);
        }
        else
        {
            tft.setTextColor(TFT_DARKGREY);
        }
        tft.drawString(TIMER_LOGS[i], 5, listOptionsPadding(line));
        line++;
    }
}

void LogsPage::drawStatusBar()
{
    page.drawStatusBar();
}

void LogsPage::enter()
{
    page.tftInit();
    drawStatusBar();

    logsCount = TIMER_LOG_NUM;
    selectedLogNum = (logsCount > 0) ? (logsCount - 1) : 0;

    drawLogs();
    page.drawButtons(RIGHT, "Exit");
}

void LogsPage::exit()
{
}

void LogsPage::handleButtonPress()
{
    ButtonType btnType = button.getButtonPressed();

    switch (btnType)
    {
    case LEFT_ONCE:

        if (logsCount == 0)
            return;
        selectedLogNum = (selectedLogNum - 1 + logsCount) % logsCount;
        delay(300);
        drawLogs();
        break;
    case RIGHT_ONCE:
        pageManager.setPage(&settingsPage);
        break;
    default:
        break;
    }
}