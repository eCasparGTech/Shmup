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

    enum Direction
    {
        up = 0,
        down = 1,
        left = 2,
        right = 3
    };

    static Direction getRandomDirection();
    Direction m_direction;

protected:
    bool enabled = true;
    bool visible = true;
};
