#include "Missile.h"

#include "GameManager.h"

Missile::Missile() {}

void Missile::start()
{
    Projectile::start();
    
    //mp_sprite->m_drawable.set
    setSize({10.0f, 10.0f});
    mp_sprite->setColor({255, 0, 0, 255});
}

void Missile::onCollisionEnter(Object* object) {
    if (object->getType() == TObstacle)
    {
        mp_gameManager->destroyObject(this);
    }
}
