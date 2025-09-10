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

    void move(sf::Vector2f* distance);
    void setDestination(sf::Vector2f* destination);
    void goToDestination();

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
    
    sf::Vector2f m_destination;
    bool m_hasDestination;
};
