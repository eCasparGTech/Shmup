#pragma once
#include "Alive.h"

class Enemy : public Alive
{
public:
    Enemy();
    ~Enemy() {}

    void update() override;
    void wander();

protected:
    enum State
    {
        idle = 0,
        wandering = 1,
        chasing = 2,
        attacking = 3
    };

    State m_state;

    
    sf::Vector2f m_destination;
};
