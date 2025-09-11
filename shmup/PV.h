#pragma once
#include "UI.h"
class GameManager;
class PV : public UI
{
public:
    PV();
    virtual ~PV() {}
    void start() override;
    void setLife(int life);

private:
    sf::Vector2f uiPosition = {4.0f, 4.0f};
    sf::Vector2f uiGap = {4.0f, 0.0f};
    std::vector<Sprite*> m_sprites;
};
