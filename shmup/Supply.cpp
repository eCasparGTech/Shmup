#include "Supply.h"

#include "GameManager.h"

Supply::Supply() {}

Supply::~Supply()
{
    mp_gameManager->destroySprite(mp_insideSprite);
    Collectible::~Collectible();
}

void Supply::start()
{
    Collectible::start();
    setSize({10.0f, 10.0f});
    mp_sprite->baseColor = {255, 255, 127, 255};
    mp_sprite->setColor(mp_sprite->baseColor);

    mp_insideSprite = mp_gameManager->createSprite();
    mp_insideSprite->setSize(mp_sprite->getSize() * 0.5f);
    mp_insideSprite->baseColor = {0, 0, 0, 127};
    mp_insideSprite->setColor(mp_insideSprite->baseColor);
    mp_insideSprite->setPosition(m_position + mp_insideSprite->getSize() * 0.5f);
}

void Supply::onCollisionEnter(Object* object)
{
    Collectible::onCollisionEnter(object);

    if (object->getType() == TPlayer)
    {
        mp_gameManager->getPlayer()->heal(m_lifeHeal);
        mp_gameManager->getPlayer()->giveAmmo(m_supplyAmmo);
    }
}

void Supply::setPosition(sf::Vector2f position)
{
    Collectible::setPosition(position);
    mp_insideSprite->setPosition(position + mp_insideSprite->getSize() * 0.5f);
}
