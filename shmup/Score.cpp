#include "Score.h"

#include "GameManager.h"
#include "Window.h"
Score::Score() {}

void Score::start()
{
    UI::start();

    mp_scoreText = mp_gameManager->createSprite();

    mp_scoreText->setPosition({
        mp_gameManager->getWindow()->getDimensions().x * 0.5f, 10.0f
    });
    mp_scoreText->setText(std::to_string(mp_gameManager->getScore()));
}

void Score::updateScore()
{
    mp_scoreText->setText(std::to_string(mp_gameManager->getScore()));
}
