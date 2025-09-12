#include "AMMO.h"
#include "GameManager.h"
#include "Window.h"

AMMO::AMMO() : UI() {}

void AMMO::start()
{
    UI::start();

    m_barWidth = mp_gameManager->getWindow()->getDimensions().x * 0.8f;

    float windowWidth = static_cast<float>(mp_gameManager->getWindow()->getDimensions().x);
    uiPosition.x = windowWidth * 0.5f;
    uiPosition.y = mp_gameManager->getWindow()->getDimensions().y - 20 + m_barHeight * 0.5f;
}

void AMMO::setMaxAmmo(int maxAmmo)
{
    m_maxAmmo = maxAmmo;

    if (m_barCreated)
    {
        mp_gameManager->destroySprite(m_border);
        mp_gameManager->destroySprite(m_background);
        mp_gameManager->destroySprite(m_fill);
        m_barCreated = false;
    }

    if (maxAmmo <= 0) return;

    // 1. Bordure (centrée)
    m_border = mp_gameManager->createSprite();
    m_border->setSize({m_barWidth + 4.0f, m_barHeight + 4.0f});
    m_border->setColor({150, 150, 150, 100});
    m_border->setPosition(uiPosition); // Le sprite se centre automatiquement

    // 2. Fond (centré)
    m_background = mp_gameManager->createSprite();
    m_background->setSize({m_barWidth, m_barHeight});
    m_background->setColor({40, 40, 40, 100});
    m_background->setPosition(uiPosition);

    // 3. Remplissage (aligné à gauche de la barre)
    m_fill = mp_gameManager->createSprite();
    m_fill->setSize({m_barWidth, m_barHeight});
    m_fill->setColor({255, 255, 255, 255});

    sf::Vector2f fillPosition = {uiPosition.x - m_barWidth * 0.5f + (m_barWidth * 0.5f), uiPosition.y};
    m_fill->setPosition(fillPosition);

    m_barCreated = true;
    m_currentAmmo = -1;
}

void AMMO::setAmmo(int ammo)
{
    if (m_currentAmmo == ammo) return;

    if (!m_barCreated)
    {
        setMaxAmmo(std::max(ammo, 100));
    }

    m_currentAmmo = ammo;

    float percentage = 0.0f;
    if (m_maxAmmo > 0)
    {
        percentage = static_cast<float>(ammo) / static_cast<float>(m_maxAmmo);
        percentage = std::max(0.0f, std::min(1.0f, percentage));
    }

    float fillWidth = m_barWidth * percentage;
    m_fill->setSize({fillWidth, m_barHeight});
    
    sf::Vector2f fillPosition = {uiPosition.x - m_barWidth * 0.5f + fillWidth * 0.5f, uiPosition.y};
    m_fill->setPosition(fillPosition);
}