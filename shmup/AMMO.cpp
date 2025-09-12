#include "AMMO.h"
#include "GameManager.h"
#include "Window.h"

AMMO::AMMO() : UI() {}

void AMMO::start()
{
    UI::start();
    uiPosition.y = mp_gameManager->getWindow()->getDimensions().y - 10;
    
    float availableWidth = static_cast<float>(mp_gameManager->getWindow()->getDimensions().x) - 20.0f; 
    m_maxAmmoPerBar = static_cast<int>(std::floor(availableWidth / 3.0f)); 
}

void AMMO::setMaxAmmo(int maxAmmo)
{
    if (m_maxAmmo == maxAmmo) return;
    
    for (auto& bar : m_ammoBars) {
        mp_gameManager->destroySprite(bar.border); 
        mp_gameManager->destroySprite(bar.background);
        mp_gameManager->destroySprite(bar.fill);
    }
    m_ammoBars.clear();
    
    m_maxAmmo = maxAmmo;
    if (maxAmmo <= 0) return;
    
    int barCount = static_cast<int>(std::ceil(static_cast<float>(maxAmmo) / static_cast<float>(m_maxAmmoPerBar)));
    float barWidth = static_cast<float>(mp_gameManager->getWindow()->getDimensions().x) - 20.0f;
    
    for (int i = 0; i < barCount; i++) {
        AmmoBar bar;
        float yPos = uiPosition.y - (static_cast<float>(i) * m_barSpacing);
        
        int ammoInThisBar = std::min(m_maxAmmoPerBar, maxAmmo - (i * m_maxAmmoPerBar));
        bar.maxAmmoInBar = ammoInThisBar;
        bar.maxWidth = (static_cast<float>(ammoInThisBar) / static_cast<float>(m_maxAmmoPerBar)) * barWidth;
        
        // 1. Bordure en arrière-plan
        bar.border = mp_gameManager->createSprite();
        bar.border->setSize({bar.maxWidth + 4.0f, m_barHeight + 4.0f});
        bar.border->setColor({100, 100, 100, 100});
        bar.border->setPosition({uiPosition.x - 2.0f, yPos - 2.0f});
        
        // 2. Fond de la barre
        bar.background = mp_gameManager->createSprite();
        bar.background->setSize({bar.maxWidth, m_barHeight});
        bar.background->setColor({30, 30, 30, 100});
        bar.background->setPosition({uiPosition.x, yPos});
        
        // 3. Barre de remplissage par-dessus
        bar.fill = mp_gameManager->createSprite();
        bar.fill->setSize({bar.maxWidth, m_barHeight});
        bar.fill->setColor({255, 255, 255, 255});
        bar.fill->setPosition({uiPosition.x, yPos});
        
        m_ammoBars.push_back(bar);
    }
    
    m_currentAmmo = -1;
}

void AMMO::setAmmo(int ammo)
{
    if (m_currentAmmo == ammo) return;
    
    if (m_ammoBars.empty() && ammo > 0) {
        setMaxAmmo(std::max(ammo, 100));
    }
    
    m_currentAmmo = ammo;
    int ammoRemaining = ammo;
    
    for (auto& bar : m_ammoBars) {
        if (ammoRemaining <= 0) {
            bar.fill->setSize({0.0f, m_barHeight});
        } else {
            int ammoInThisBar = std::min(bar.maxAmmoInBar, ammoRemaining);
            float fillRatio = static_cast<float>(ammoInThisBar) / static_cast<float>(bar.maxAmmoInBar);
            float fillWidth = bar.maxWidth * fillRatio;
            
            bar.fill->setSize({fillWidth, m_barHeight});
            ammoRemaining -= ammoInThisBar;
        }
    }
}