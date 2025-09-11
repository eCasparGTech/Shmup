#pragma once
#include "Entity.h"

class Collectible: public Entity
{
public:
    Collectible();
    void onCollisionEnter(Object* object);
    virtual ~Collectible() {}

    void start() override;
};
