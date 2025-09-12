#pragma once
#include "Collectible.h"

class Supply: public Collectible
{
public:
    Supply();
    virtual ~Supply();

    void start() override;

    int m_lifeHeal = 1;
    int m_supplyAmmo = 200;

    void onCollisionEnter(Object* object) override;

    void setPosition(sf::Vector2f position) override;
    
private:
    Sprite* mp_insideSprite;
};
