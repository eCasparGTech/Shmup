#include "Object.h"
#include "GameManager.h"

Object::Object()
{
    mp_sprite = new Sprite();
}


void Object::move(sf::Vector2f distance)
{
    m_position += distance;
    mp_sprite->setPosition(m_position);
}

/*
void Object::rotate(float rotation)
{
    m_rotation += rotation;
}

void Object::scale(float width, float height)
{
    m_width += width;
    m_height += height;
}
*/

void Object::setGameManager(GameManager* manager)
{
    manager->subscribe(mp_sprite);
}
