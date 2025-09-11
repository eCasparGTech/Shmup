#include "PV.h"

#include "GameManager.h"

PV::PV() : UI() {}

void PV::start()
{
    UI::start();
    m_sprite = mp_gameManager->createSprite();
    m_sprite->setSize({20.0f, 20.0f});
    m_sprite->setColor(sf::Color::Red);
    m_sprite->setPosition({10.0f, 10.0f});

    m_sprite2 = new Sprite();
    m_sprite2->setSize({15.0f, 15.0f});
    m_sprite2->setColor(sf::Color::White);
    m_sprite2->setPosition({10.0f, 10.0f});

    
}
