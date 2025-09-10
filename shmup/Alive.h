#pragma once
#include "Entity.h"

class GameManager;

class Alive : public Entity
{
public:
    Alive();
    virtual ~Alive() {}

    enum AttackType
    {
        Projectile = 0
    };

    void Attack(AttackType attackType);
    
private:
    unsigned int mp_attackTime;
    unsigned int mp_attackCooldown;
};
