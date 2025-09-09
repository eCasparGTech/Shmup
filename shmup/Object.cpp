#include "Object.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Timer.h"

Object::Object()
{
    mp_sprite = new Sprite();
    mp_gameManager = GameManager::getInstance();
}

void Object::update()
{
    // collider
}

void Object::setPosition(sf::Vector2f position)
{
    m_position = position;
    mp_sprite->setPosition(position);
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
    manager->subscribe(this);
}
