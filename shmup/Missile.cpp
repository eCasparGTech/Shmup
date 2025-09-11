#include "Missile.h"

#include "GameManager.h"

Missile::Missile() {}

void Missile::start()
{
    Projectile::start();
    
    //mp_sprite->m_drawable.set
    setSize({4.0f, 12.0f});
    mp_sprite->setColor({255, 0, 0, 255});
}

void Missile::onCollisionEnter(Object* object) {
    if (object->getType() == TObstacle || object->getType() == TEnemy)
    {
        mp_gameManager->destroyObject(this);
    }
}
