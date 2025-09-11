#pragma once
#include "Entity.h"

class GameManager;

class Alive : public Entity
{
public:
    Alive();
    virtual ~Alive() {}

    void start() override;
    void update() override;

    enum AttackType
    {
        Projectile = 0
    };

    void Attack(AttackType attackType);
    void takeDamage(int damage);
    virtual void die();

    void setLife(int life) { mp_life = life; }
    int getLife() { return mp_life; }

private:
    float mp_attackTime;
    float mp_attackCooldown;
    int mp_life = 20;

    bool  m_hitActive = false;
    float m_hitUntil  = 0.0f;
    float m_sizeMultiplierOnHit = 1.2f;
};
