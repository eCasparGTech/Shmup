#include "PV.h"

#include "GameManager.h"

PV::PV() : UI() {}

void PV::start()
{
    UI::start();
}

void PV::setLife(int life)
{
    for (auto sprite : m_sprites)
    {
        mp_gameManager->destroySprite(sprite);
    }
    m_sprites.clear();
    
    for (int i = 0; i < life; i++)
    {
        Sprite* m_sprite = mp_gameManager->createSprite();
        m_sprite->setSize({10.0f, 10.0f});
        m_sprite->setColor({255, 0, 0, 255});
        sf::Vector2f position = {uiPosition.x + i * (uiGap.x + m_sprite->getSize().x), uiPosition.y};
        m_sprite->setPosition(position);

        Sprite* m_spriteInside = mp_gameManager->createSprite();
        sf::Vector2f size = m_sprite->getSize() * 0.5f;
        m_spriteInside->setSize(size);
        m_spriteInside->setColor({255, 255, 255, 150});
        sf::Vector2f m_spriteInsidePosition = position + size * 0.5f;
        m_spriteInside->setPosition(m_spriteInsidePosition);

        m_sprites.push_back(m_sprite);
        m_sprites.push_back(m_spriteInside);
    }
}
