#include "../include/core/page_manager.h"

PageManager::PageManager()
{
    currentPage = nullptr;
}

void PageManager::setPage(Page *newPage)
{
    if (currentPage)
    {
        currentPage->exit();
    }
    currentPage = newPage;
    delay(800);
    loadThemeColors();
    loadPlatesAndBoards();
    loadEditAfterMatchBoards();
    loadTimerLogs();
    loadRandomValue();
    resetReceivedData();
    currentPage->enter();
}

Page *PageManager::getCurrentPage()
{
    return currentPage;
}

void PageManager::handleButtonPress()
{
    if (currentPage != nullptr)
    {
        currentPage->handleButtonPress();
    }
}