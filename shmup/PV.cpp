#include "PV.h"

#include "GameManager.h"
#include "Window.h"

PV::PV() : UI() {}

void PV::start()
{
    UI::start();


    float ammoBarX = mp_gameManager->getWindow()->getDimensions().x * 0.5f;
    float ammoBarWidth = mp_gameManager->getWindow()->getDimensions().x * 0.8f;
    uiPosition.x = ammoBarX - ammoBarWidth * 0.5f;
    uiPosition.y = mp_gameManager->getWindow()->getDimensions().y - 50;
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


        float heartSpacing = 10.0f + uiGap.x;
        sf::Vector2f position = {
            uiPosition.x + (5.0f + i * heartSpacing),
            uiPosition.y
        };
        m_sprite->setPosition(position);

        Sprite* m_spriteInside = mp_gameManager->createSprite();
        sf::Vector2f size = m_sprite->getSize() * 0.5f;
        m_spriteInside->setSize(size);
        m_spriteInside->setColor({255, 255, 255, 150});

        m_spriteInside->setPosition(position);

        m_sprites.push_back(m_sprite);
        m_sprites.push_back(m_spriteInside);
    }
}
