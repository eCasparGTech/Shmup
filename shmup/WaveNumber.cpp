#include "WaveNumber.h"

#include "GameManager.h"
#include "Window.h"

WaveNumber::WaveNumber() {}

void WaveNumber::start()
{
    UI::start();
}

void WaveNumber::displayWaveNumber()
{
    Sprite* mp_waveNumberText = mp_gameManager->createSprite();
    
    mp_waveNumberText->setPosition({mp_gameManager->getWindow()->getDimensions().x * 0.5f, mp_gameManager->getWindow()->getDimensions().y * 0.5f});
    mp_waveNumberText->setText(std::to_string(mp_gameManager->m_wave));
}
