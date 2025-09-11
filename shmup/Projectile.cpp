#include "Projectile.h"

#include "GameManager.h"

Projectile::Projectile()
{
    setType(ObjectType::TProjectile);
    m_moveSpeed = 500.0f;
    mp_birthtime = Timer::getTime();
    mp_lifetime = 5.0f;
}

void Projectile::update()
{
    Entity::update();

    move(getDirection());

    float age = Timer::getTime() - mp_birthtime;
    if (age >= mp_lifetime)
    {
        mp_gameManager->destroyObject(this);
        return;
    }
    
}
