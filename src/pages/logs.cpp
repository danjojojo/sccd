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
    page.drawPaginatedLogs(logsCount, selectedLogNum);
}

void LogsPage::drawStatusBar()
{
    page.drawStatusBar();
}

void LogsPage::enter()
{
    logsCount = TIMER_LOG_NUM;
    Serial.print("Logs count: ");
    Serial.println(logsCount);
    getItemsPerPage(logsCount);
    selectedLogNum = (logsCount > 0) ? (logsCount - 1) : 0;
    
    page.tftInit();
    drawStatusBar();
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