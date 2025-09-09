#pragma once
#include "Alive.h"

class Enemy : public Alive
{
public:
    Enemy();
    ~Enemy() {}

    void update() override;
    void wander();

    enum Direction
    {
        up = 0,
        down = 1,
        left = 2,
        right = 3
    };
    
    Direction getRandomDirection();

protected:
    enum State
    {
        idle = 0,
        wandering = 1,
        chasing = 2,
        attacking = 3
    };

    State m_state;

    Direction m_direction;
    sf::Vector2f m_destination;
};
