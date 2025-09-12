#include "HurtOverlay.h"

#include "GameManager.h"
#include "Window.h"

HurtOverlay::HurtOverlay() {}

void HurtOverlay::start()
{
    UI::start();

    mp_hurtOverlay = mp_gameManager->createSprite();
    mp_hurtOverlay->setSize({ static_cast<float>(mp_gameManager->getWindow()->getDimensions().x),
        static_cast<float>(mp_gameManager->getWindow()->getDimensions().y) });
    mp_hurtOverlay->setColor({ 255, 0, 0, 31 });
    mp_hurtOverlay->setPosition({ -5000.0f, -5000.0f });
}

void HurtOverlay::showHurtOverlay()
{
    mp_hurtOverlay->setPosition({ static_cast<float>(mp_gameManager->getWindow()->getDimensions().x) * 0.5f,
        static_cast<float>(mp_gameManager->getWindow()->getDimensions().y) * 0.5f });
}

void HurtOverlay::hideHurtOverlay()
{
    mp_hurtOverlay->setPosition({ -5000.0f, -5000.0f });
}
