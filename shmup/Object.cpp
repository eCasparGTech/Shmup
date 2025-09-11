#include "Object.h"

#include "GameManager.h"

Object::Object() {}

void Object::start()
{
    mp_sprite = new Sprite();
    mp_gameManager = GameManager::getInstance();
    m_position = sf::Vector2f(0.0f, 0.0f);
    setSize({100.0f, 100.0f});
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
    mp_sprite->setSize(size);
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

sf::Vector2f Object::getPosition()
{
    return m_position;
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

bool Object::isColliding(Object* a, Object* b)
{
    return isColliding(a->m_position, a->getSize(), b->m_position, b->getSize());
}

bool Object::isColliding(sf::Vector2f aPosition, sf::Vector2f aSize, sf::Vector2f bPosition, sf::Vector2f bSize)
{
    return aPosition.x < bPosition.x + bSize.x
        && aPosition.x + aSize.x > bPosition.x
        && aPosition.y < bPosition.y + bSize.y
        && aPosition.y + aSize.y > bPosition.y;
}

bool Object::isCollidingWith(Object* objectB)
{
    return isColliding(this, objectB);
}


bool Object::wouldCollideAt(sf::Vector2f& aPosition, sf::Vector2f& aSize)
{
    for (Object* bObject : mp_gameManager->getObjects())
    {
        if (bObject == this) continue;
        if (bObject->getType() != ObjectType::TObstacle) continue;

        sf::Vector2f bPosition = bObject->getPosition();
        sf::Vector2f oSize = bObject->getSize();
        if (isColliding(aPosition, aSize, bPosition, oSize))
            return true;
    }
    return false;
}