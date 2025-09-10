#include "Projectile.h"

#include "GameManager.h"

Projectile::Projectile()
{
    m_moveSpeed = 1.0f;
    mp_birthtime = Timer::getTime();
    mp_lifetime = 500.0f;
}

void Projectile::update()
{
    Entity::update();
    
    move(getDirection());

    float age = static_cast<float>(Timer::getTime() - mp_birthtime);
    if (age >= mp_lifetime)
    {
        mp_gameManager->destroyObject(this);
    }
}
