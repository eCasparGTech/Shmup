#include "Entity.h"

#include "framework.h"
#include "GameManager.h"
#include "Timer.h"

static float length(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

static sf::Vector2f normalize(const sf::Vector2f& v)
{
    float len = length(v);
    if (len <= 1e-6f) return {0.f, 0.f};
    return {v.x / len, v.y / len};
}

Entity::Entity() {}

void Entity::start()
{
    Object::start();
    m_moveSpeed = 200.0f;
    m_timer = mp_gameManager->getTimer();

    m_hasDestination = false;
    m_enabled = true;
    m_visible = true;
    m_direction = up;
}

void Entity::update()
{
    Object::update();
    if (m_hasDestination)
    {
        goToDestination();
    }
}

void Entity::move(const sf::Vector2f& inputDirection)
{
    sf::Vector2f dir = normalize(inputDirection);
    if (dir.x == 0.f && dir.y == 0.f) return;

    const float dt   = m_timer ? m_timer->getDelta() : 0.f;
    const float step = m_moveSpeed * dt;

    // Tentative diagonale
    sf::Vector2f next = m_position + dir * step;
    sf::Vector2f size = getSize();
    if (!wouldCollideAt(next, size)) {
        m_position = next;
        setPosition(m_position);
        return;
    }

    bool moved = false;

    if (dir.x != 0.f) {
        sf::Vector2f nextX{ m_position.x + dir.x * step, m_position.y };
        if (!wouldCollideAt(nextX, size)) {
            m_position.x = nextX.x;
            moved = true;
        }
    }

    if (dir.y != 0.f) {
        sf::Vector2f nextY{ m_position.x, m_position.y + dir.y * step };
        if (!wouldCollideAt(nextY, size)) {
            m_position.y = nextY.y;
            moved = true;
        }
    }

    if (moved) setPosition(m_position);
}

void Entity::move(Direction direction)
{
    move(toVector(direction));
}

void Entity::setDestination(const sf::Vector2f& destination)
{
    m_destination = destination;
    m_hasDestination = true;
}

Entity::Direction Entity::getRandomDirection()
{
    return static_cast<Direction>(std::rand() % 4);
}

void Entity::goToDestination()
{
    if (!m_hasDestination) return;

    sf::Vector2f difference = m_destination - m_position;
    float distance = length(difference);
    float step = m_moveSpeed * m_timer->getDelta();
    float max = abs(std::max(difference.x, difference.y));

    if (step >= distance || max == 0.0f)
    {
        m_hasDestination = false;
        m_destinationReached = true;
        return;
    }

    std::cout << "max: " << max << std::endl;
    sf::Vector2f inputDirection = { difference.x / max, difference.y / max };
    move(inputDirection);
}

sf::Vector2f Entity::getDirection() const
{
    return toVector(m_direction);
}

sf::Vector2f Entity::toVector(Direction direction)
{
    switch (direction)
    {
    case up: return {0.f, -1.f};
    case down: return {0.f, 1.f};
    case left: return {-1.f, 0.f};
    case right: return {1.f, 0.f};
    default: return {0.f, 0.f};
    }
}
