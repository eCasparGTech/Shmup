#include "Object.h"

#include "GameManager.h"

Object::Object() {}
Object::~Object()
{
    mp_gameManager->destroySprite(mp_sprite);
}

void Object::start()
{
    mp_gameManager = GameManager::getInstance();
    mp_sprite = mp_gameManager->createSprite();
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

bool Object::isOverlappingStrict(sf::Vector2f aPos, sf::Vector2f aSize,
                                 sf::Vector2f bPos, sf::Vector2f bSize)
{
    return aPos.x < bPos.x + bSize.x &&
        aPos.x + aSize.x > bPos.x &&
        aPos.y < bPos.y + bSize.y &&
        aPos.y + aSize.y > bPos.y;
}

bool Object::isTouchingOrOverlapping(sf::Vector2f aPos, sf::Vector2f aSize,
                                     sf::Vector2f bPos, sf::Vector2f bSize,
                                     float eps)
{
    bool x = (aPos.x <= bPos.x + bSize.x + eps) && (aPos.x + aSize.x >= bPos.x - eps);
    bool y = (aPos.y <= bPos.y + bSize.y + eps) && (aPos.y + aSize.y >= bPos.y - eps);
    return x && y;
}

bool Object::isColliding(sf::Vector2f aPos, sf::Vector2f aSize,
                         sf::Vector2f bPos, sf::Vector2f bSize)
{
    return isTouchingOrOverlapping(aPos, aSize, bPos, bSize, CONTACT_EPS);
}

bool Object::isColliding(Object* a, Object* b)
{
    return isColliding(a->m_position, a->getSize(), b->m_position, b->getSize());
}

bool Object::isCollidingWith(Object* objectB)
{
    return isColliding(this, objectB);
}

bool Object::isCollidingWithAnyObstacle()
{
    for (Object* object : mp_gameManager->getObjects())
    {
        if (object->getType() == TObstacle)
        {
            if (isColliding(this, object))
            {
                return true;
            }
        }
    }
    return false;
}

bool Object::wouldCollideAt(const sf::Vector2f& aPosition, const sf::Vector2f& aSize) const
{
    for (Object* bObject : mp_gameManager->getObjects())
    {
        if (bObject == this) continue;
        if (bObject->getType() == TProjectile || mp_objectType == TProjectile || mp_objectType == TCollectible) continue;

        const sf::Vector2f bPosition = bObject->getPosition();
        const sf::Vector2f bSize = bObject->getSize();
        if (isOverlappingStrict(aPosition, aSize, bPosition, bSize))
            return true;
    }
    return false;
}
