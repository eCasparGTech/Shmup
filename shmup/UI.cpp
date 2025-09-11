#include "UI.h"

#include "GameManager.h"

class GameManager;

UI::UI() {}

void UI::start()
{
    mp_gameManager = GameManager::getInstance();
}

