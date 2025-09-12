#include "WaveNumber.h"

#include "GameManager.h"
#include "Window.h"

WaveNumber::WaveNumber() {}

void WaveNumber::start()
{
    UI::start();
    
    mp_waveNumberText = mp_gameManager->createSprite();
    mp_waveNumberText->setPosition({ -500.0f, -500.0f });
}

void WaveNumber::showWaveNumber()
{
    mp_waveNumberText->setText("Wave " + std::to_string(mp_gameManager->m_wave + 1));
    mp_waveNumberText->setPosition({mp_gameManager->getWindow()->getDimensions().x * 0.5f, mp_gameManager->getWindow()->getDimensions().y * 0.5f});
}

void WaveNumber::hideWaveNumber()
{
    mp_waveNumberText->setPosition({ -500.0f, -500.0f });
}
