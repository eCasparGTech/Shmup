#include "AMMO.h"

#include "GameManager.h"
#include "Window.h"

AMMO::AMMO() : UI() {}

void AMMO::start()
{
    UI::start();
}

void AMMO::setAmmo(int ammo)
{
    for (auto sprite : m_sprites)
    {
        mp_gameManager->destroySprite(sprite);
    }
    m_sprites.clear();

    int maxAmmoPerLine = static_cast<int>(std::floor((static_cast<float>(mp_gameManager->getWindow()->getDimensions().x) - 7.0f) / 3.0f));
    int lineCount = static_cast<int>(std::ceil(static_cast<float>(ammo) / static_cast<float>(maxAmmoPerLine)));
    
    int ammoRemaining = ammo;

    for (int i = 0; i < lineCount; i++)
    {
        float yPosition = uiPosition.y - (static_cast<float>(i) * 7.0f);

        int ammoInLine = ammoRemaining > maxAmmoPerLine ? maxAmmoPerLine : ammoRemaining;
        ammoRemaining -= ammoInLine;
        for (int j = 0; j < ammoInLine; j++)
        {
            Sprite* m_sprite = mp_gameManager->createSprite();
            m_sprite->setSize({2.0f, 6.0f});
            m_sprite->setColor({255, 255, 255, 255});
    
            sf::Vector2f position = {uiPosition.x + j * (uiGap.x + m_sprite->getSize().x), yPosition};
            m_sprite->setPosition(position);

            Sprite* m_spriteInside = mp_gameManager->createSprite();
            sf::Vector2f size = m_sprite->getSize() * 0.5f;
            m_spriteInside->setSize(size);
            m_spriteInside->setColor({0, 0, 0, 127});
            m_spriteInside->setPosition(position + size * 0.5f);

            m_sprites.push_back(m_sprite);
            m_sprites.push_back(m_spriteInside);
        }
    }
}
