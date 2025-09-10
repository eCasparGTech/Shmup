#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile();
    virtual ~Projectile() {}

    enum ProjectileType
    {
        
    };

    void update() override;

private:
    unsigned int mp_birthtime;
    float mp_lifetime;
};
