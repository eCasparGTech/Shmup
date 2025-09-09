#pragma once
#include "Object.h"
#include "Timer.h"

class Entity : public Object
{
public:
    Entity();

    virtual ~Entity() {}

    float m_moveSpeed;
    Timer* m_timer;

    void move(sf::Vector2f distance);
    void goTo(sf::Vector2f position);

protected:
    bool enabled = true;
    bool visible = true;
};
