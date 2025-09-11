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
    virtual void heal(int amount);

    enum AttackType
    {
        Projectile = 0
    };

    void Attack(AttackType attackType);
    virtual void takeDamage(int damage);
    virtual void die();

    void setLife(int life) { mp_life = life; }
    int getLife() { return mp_life; }

protected:
    int mp_life = 10;
    int mp_maxLife = 10;
private:
    float mp_attackTime;
    float mp_attackCooldown;

    bool  m_hitActive = false;
    float m_hitUntil  = 0.0f;
};
