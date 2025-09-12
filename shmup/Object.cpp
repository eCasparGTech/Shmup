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
    sf::Vector2f aTopLeft = {aPos.x - aSize.x * 0.5f, aPos.y - aSize.y * 0.5f};
    sf::Vector2f bTopLeft = {bPos.x - bSize.x * 0.5f, bPos.y - bSize.y * 0.5f};
    
    return aTopLeft.x < bTopLeft.x + bSize.x &&
           aTopLeft.x + aSize.x > bTopLeft.x &&
           aTopLeft.y < bTopLeft.y + bSize.y &&
           aTopLeft.y + aSize.y > bTopLeft.y;
}

bool Object::isTouchingOrOverlapping(sf::Vector2f aPos, sf::Vector2f aSize,
                                     sf::Vector2f bPos, sf::Vector2f bSize,
                                     float eps)
{
    sf::Vector2f aTopLeft = {aPos.x - aSize.x * 0.5f, aPos.y - aSize.y * 0.5f};
    sf::Vector2f bTopLeft = {bPos.x - bSize.x * 0.5f, bPos.y - bSize.y * 0.5f};
    
    bool x = (aTopLeft.x <= bTopLeft.x + bSize.x + eps) && (aTopLeft.x + aSize.x >= bTopLeft.x - eps);
    bool y = (aTopLeft.y <= bTopLeft.y + bSize.y + eps) && (aTopLeft.y + aSize.y >= bTopLeft.y - eps);
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
        if (bObject->getType() == TProjectile || mp_objectType == TProjectile ||
            bObject->getType() == TCollectible || mp_objectType == TCollectible)
            continue;

        const sf::Vector2f bPosition = bObject->getPosition();
        const sf::Vector2f bSize = bObject->getSize();
        if (isOverlappingStrict(aPosition, aSize, bPosition, bSize))
            return true;
    }
    return false;
}
