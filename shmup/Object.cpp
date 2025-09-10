#include "Object.h"

#include "GameManager.h"

Object::Object()
{
    mp_sprite = new Sprite();
    mp_gameManager = GameManager::getInstance();
    m_position = sf::Vector2f(0.0f, 0.0f);
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

float Object::getDistance(Object* objectA, Object* objectB)
{
    sf::Vector2f aPosition = objectA->m_position;
    sf::Vector2f bPosition = objectB->m_position;
    return getDistance(&aPosition, &bPosition);
}

float Object::getDistance(sf::Vector2f* aPosition, sf::Vector2f* bPosition)
{
    return sqrt(
        (bPosition->x - aPosition->x) * (bPosition->x - aPosition->x)
        + (bPosition->y - aPosition->y) * (bPosition->y - aPosition->y)
    );
}
