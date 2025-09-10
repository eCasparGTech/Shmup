#pragma once
#include "Entity.h"
#include "Projectile.h"

class GameManager;

class Alive : public Entity
{
public:
    Alive();
    virtual ~Alive() {}

    template <class T>
    void Attack();
};

#include "Alive.tpp"