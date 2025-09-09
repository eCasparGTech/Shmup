#pragma once
#include "Object.h"

class Entity : public Object
{
public:
    Entity();
    virtual ~Entity(){}
    
    void move(sf::Vector2f distance);
};
