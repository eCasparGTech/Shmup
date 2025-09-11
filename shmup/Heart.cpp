#include "Heart.h"

#include "GameManager.h"

Heart::Heart() {}

Heart::~Heart()
{
    mp_gameManager->destroySprite(mp_insideHeart);
    Entity::~Entity();
}

void Heart::start()
{
    Collectible::start();
    setSize({10.0f, 10.0f});
    mp_sprite->baseColor = {255, 0, 0, 255};
    mp_sprite->setColor(mp_sprite->baseColor);

    mp_insideHeart = mp_gameManager->createSprite();
    mp_insideHeart->setSize(mp_sprite->getSize() * 0.5f);
    mp_insideHeart->baseColor = {255, 255, 255, 150};
    mp_insideHeart->setColor(mp_insideHeart->baseColor);
    mp_insideHeart->setPosition(m_position + mp_insideHeart->getSize() * 0.5f);
}

void Heart::onCollisionEnter(Object* object)
{
    Collectible::onCollisionEnter(object);

    if (object->getType() == TPlayer)
    {
        mp_gameManager->getPlayer()->heal(m_lifeHeal);
    }
}

void Heart::setPosition(sf::Vector2f position)
{
    Collectible::setPosition(position);
    mp_insideHeart->setPosition(position + mp_insideHeart->getSize() * 0.5f);
}
