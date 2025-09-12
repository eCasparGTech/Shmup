#pragma once
#include "UI.h"

class GameManager;

class AMMO : public UI
{
public:
    AMMO();
    virtual ~AMMO() {}
    void start() override;
    void setAmmo(int ammo);
    void setMaxAmmo(int maxAmmo);

private:
    struct AmmoBar
    {
        Sprite* background;
        Sprite* fill;
        Sprite* border;
        float maxWidth;
        int maxAmmoInBar;
    };

    sf::Vector2f uiPosition = {4.0f, 0.0f};
    float m_barHeight = 6.0f;
    float m_barSpacing = 8.0f;
    std::vector<AmmoBar> m_ammoBars;
    int m_currentAmmo = -1;
    int m_maxAmmo = 0;
    int m_maxAmmoPerBar = 0;
};
