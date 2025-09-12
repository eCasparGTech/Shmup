#pragma once
#include "Alive.h"
#include "AMMO.h"

class Keyboard;

class Player : public Alive
{
public:
    Player();
    virtual ~Player(){}
    
    void start() override;
    void update() override;
    void onCollisionEnter(Object* other) override;
    void onCollisionExit(Object* other) override;
    void handleInput();
    void heal(int amount) override;
    void giveAmmo(int amount);
    void takeDamage(int damage) override;
    void die() override;

    sf::Vector2f m_aimDirection;
    float m_aimAngle;

private:
    Keyboard* keyboard;

    unsigned int mp_ammoCount;
};
