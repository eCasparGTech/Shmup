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

void Entity::move(const sf::Vector2f& inputDirection)
{
    sf::Vector2f dir = normalize(inputDirection);
    if (dir.x == 0.f && dir.y == 0.f) return;

    float dt = m_timer ? m_timer->getDelta() : 0.f;
    float step = m_moveSpeed * dt;

    m_position += dir * step;
    setPosition(m_position);
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

    sf::Vector2f diff = m_destination - m_position;
    float dist = length(diff);
    float dt = m_timer ? m_timer->getDelta() : 0.f;
    float step = m_moveSpeed * dt;

    if (dist <= 0.001f || step >= dist)
    {
        m_position = m_destination;
        m_hasDestination = false;
        setPosition(m_position);
        return;
    }

    sf::Vector2f dir = diff / dist;
    m_position += dir * step;
    setPosition(m_position);
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
