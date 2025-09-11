#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile();
    virtual ~Projectile() {}

    enum ProjectileType {};

    void start() override;
    void update() override;

private:
    float mp_birthtime;
    float mp_lifetime;
};
