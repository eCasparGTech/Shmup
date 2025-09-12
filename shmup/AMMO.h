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

private:
    sf::Vector2f uiPosition = {4.0f, 796.0f};
    sf::Vector2f uiGap = {3.0f, 0.0f};
    std::vector<Sprite*> m_sprites;
};
