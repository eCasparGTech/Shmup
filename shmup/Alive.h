#pragma once
#include "Entity.h"

class GameManager;

class Alive : public Entity
{
public:
    Alive();
    virtual ~Alive() {}

    void start() override;
    enum AttackType
    {
        Projectile = 0
    };

    void Attack(AttackType attackType);

private:
    float mp_attackTime;
    float mp_attackCooldown;
};
