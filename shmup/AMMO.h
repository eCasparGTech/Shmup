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


    sf::Vector2f uiPosition = {0.0f, 0.0f};
private:
    Sprite* m_background;
    Sprite* m_fill;
    Sprite* m_border;

    float m_barWidth;
    float m_barHeight = 8.0f;
    int m_currentAmmo = -1;
    int m_maxAmmo = 100;
    bool m_barCreated = false;
};
