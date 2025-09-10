#pragma once
#include "Projectile.h"

class Missile : public Projectile
{
public:
    Missile();
    virtual ~Missile() {}

    float mp_cooldown = 2000.0f;
};
