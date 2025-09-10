#include "Entity.h"

#include <iostream>
#include <ostream>

#include "framework.h"
#include "GameManager.h"
#include "Timer.h"

Entity::Entity()
{
    m_moveSpeed = 0.2f;
    m_timer = mp_gameManager->getTimer();
    
    m_hasDestination = false;
    m_enabled = true;
    m_visible = true;
}

void Entity::move(sf::Vector2f* direction)
{
    float speed = m_moveSpeed * m_timer->getDelta();
    m_position += *direction * speed;
    mp_sprite->setPosition(m_position);
}

void Entity::setDestination(sf::Vector2f* destination)
{
    m_destination = *destination;
    m_hasDestination = true;
}


Entity::Direction Entity::getRandomDirection()
{
    return static_cast<Direction>(rand() % 4);
}

void Entity::goToDestination()
{
    if (!m_hasDestination) return;
    sf::Vector2f difference = m_destination - m_position;
    if (Object::getDistance(&m_position, &m_destination) > 5)
    {
        sf::Vector2f direction = {
            difference.x / (static_cast<int>(difference.x) == 0 ? 1 : abs(difference.x)),
            difference.y / (static_cast<int>(difference.y) == 0 ? 1 : abs(difference.y))
        };
        move(&direction);
    }
}
