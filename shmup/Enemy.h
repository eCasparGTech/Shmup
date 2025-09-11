#pragma once
#include "Alive.h"

class Player;

class Enemy : public Alive
{
public:
    Enemy();
    ~Enemy() {}

    void start() override;
    void update() override;
    void wander();
    void attack();

protected:
    bool m_sleeping;
    float m_sleepTime;
    float m_sleepDuration;

    bool m_attacking;
    bool m_charging;
    bool m_releasing;

    enum MovingState
    {
        idle,
        wandering,
        chasing,
    };

    MovingState m_movingState;

private:
    Player* mp_player;

    bool m_unstuckActive;
    float m_unstuckUntil;

    sf::Vector2f m_attackStartPos;
    float m_attackChargeStartTime;
    float m_minMoveBeforeDash;
};
