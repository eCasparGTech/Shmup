#include "Object.h"

#include "GameManager.h"

Object::Object()
{
    mp_sprite = new Sprite();
    mp_gameManager = GameManager::getInstance();
    m_position = sf::Vector2f(0.0f, 0.0f);
}

void Object::setWidth(float width)
{
    mp_width = width;
    mp_sprite->setWidth(width);
}

void Object::setHeight(float height)
{
    mp_height = height;
    mp_sprite->setHeight(height);
}

void Object::setSize(sf::Vector2f size)
{
    setWidth(size.x);
    setHeight(size.y);
}

sf::Vector2f Object::getSize()
{
    return {mp_width, mp_height};
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

bool Object::isColliding(Object* objectA, Object* objectB)
{
    // check if rect is in rect
    sf::Vector2f aPosition = objectA->m_position;
    sf::Vector2f bPosition = objectB->m_position;
    sf::Vector2f aSize = objectA->getSize();
    sf::Vector2f bSize = objectB->getSize();
    return aPosition.x < bPosition.x + bSize.x
        && aPosition.x + aSize.x > bPosition.x
        && aPosition.y < bPosition.y + bSize.y
        && aPosition.y + aSize.y > bPosition.y;
}

bool Object::isCollidingWith(Object* objectB)
{
    return isColliding(this, objectB);
}


