#include "Entity.h"

#include "GameManager.h"
#include "Timer.h"

Entity::Entity()
{
    m_moveSpeed = 0.2f;
    m_timer = mp_gameManager->getTimer();
}

void Entity::move(sf::Vector2f direction)
{
    float speed = m_moveSpeed * m_timer->getDelta();
    m_position += direction * speed;
    mp_sprite->setPosition(m_position);
}
