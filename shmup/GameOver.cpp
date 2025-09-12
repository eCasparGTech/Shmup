#include "GameOver.h"

#include "GameManager.h"
#include "Window.h"

GameOver::GameOver() {}

void GameOver::start()
{
    UI::start();
}

void GameOver::displayGameOver()
{
    Sprite* mp_gameOverText = mp_gameManager->createSprite();
    
    mp_gameOverText->setPosition({mp_gameManager->getWindow()->getDimensions().x * 0.5f, mp_gameManager->getWindow()->getDimensions().y * 0.5f});
    mp_gameOverText->setText("Game Over");
}
