#include "Alive.h"

#include "GameManager.h"
#include "Missile.h"

Alive::Alive()
{
    mp_attackTime = 0.0f;
    mp_attackCooldown = 0.1f;
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
