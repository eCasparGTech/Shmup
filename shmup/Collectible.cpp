#include "Collectible.h"

#include "GameManager.h"

Collectible::Collectible() {}

void Collectible::onCollisionEnter(Object* object)
{
    if (object->getType() == TPlayer)
    {
        mp_gameManager->destroyObject(this);
    }
}

void Collectible::start()
{
    Entity::start();
    setType(TCollectible);
}
        