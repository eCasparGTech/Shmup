#include "Entity.h"

Entity::Entity()
{
}

void Entity::move(sf::Vector2f distance)
{
    m_position += distance;
    mp_sprite->setPosition(m_position);
}
