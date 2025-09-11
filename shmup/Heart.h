#pragma once
#include "Collectible.h"

class Heart: public Collectible
{
public:
    Heart();
    virtual ~Heart();

    void start() override;

    int m_lifeHeal = 1;

    void onCollisionEnter(Object* object) override;

    void setPosition(sf::Vector2f position) override;
    
private:
    Sprite* mp_insideHeart;
};
