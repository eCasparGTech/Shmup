#pragma once
#include "Projectile.h"

class Missile : public Projectile
{
public:
    Missile();
    virtual ~Missile() {}
    void start() override;

    float mp_cooldown = 2.0f;
};
