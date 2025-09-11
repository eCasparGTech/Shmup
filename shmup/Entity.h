#pragma once
#include "Object.h"
#include "Timer.h"
#include <SFML/System/Vector2.hpp>

class Entity : public Object
{
public:
    enum Direction
    {
        up = 0,
        down = 1,
        left = 2,
        right = 3
    };

    Entity();
    virtual ~Entity() {}

    void start() override;
    void update() override;

    void move(const sf::Vector2f& inputDirection);
    void move(Direction direction);

    void setDestination(const sf::Vector2f& destination);
    void goToDestination();

    sf::Vector2f getDirection() const;
    static sf::Vector2f toVector(Direction direction);
    static Direction getRandomDirection();


    void setStuckParams(float timeSeconds, float minMovePixels);
    bool isStuck() const;
    void resetStuckProbe();

    float m_moveSpeed;
    Timer* m_timer;
    Direction m_direction;

protected:
    bool m_enabled;
    bool m_visible;

    sf::Vector2f m_destination;
    bool m_hasDestination;
    bool m_destinationReached;


    void updateStuckDetector();
    sf::Vector2f m_stuckLastPos;
    float m_lastSignificantMoveTime;
    float m_stuckTimeThreshold;
    float m_stuckMinMove;
    bool m_stuck;
};
