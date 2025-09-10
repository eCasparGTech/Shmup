#include "Alive.h"

#include "GameManager.h"
#include "Missile.h"

Alive::Alive()
{
    mp_attackTime = 0;
    mp_attackCooldown = 100;
}

void Alive::Attack(AttackType attackType)
{
    switch (attackType)
    {
    case Projectile:
        if (Timer::getTime() - mp_attackTime < mp_attackCooldown) break;
        Missile* missile = mp_gameManager->createObject<Missile>();
        missile->setPosition(this->m_position);
        mp_attackTime = Timer::getTime();
        break;
    }
}
