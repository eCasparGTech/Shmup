#include "Alive.h"

#include "GameManager.h"
#include "Missile.h"

Alive::Alive() {}

void Alive::start()
{
    Entity::start();
    mp_attackTime = 0.0f;
    mp_attackCooldown = 0.05f;
}

void Alive::Attack(AttackType attackType)
{
    switch (attackType)
    {
    case Projectile:
        if (Timer::getTime() - mp_attackTime < mp_attackCooldown) break;
        Missile* missile = mp_gameManager->createObject<Missile>();
        sf::Vector2f spawnPosition = { getPosition().x + getSize().x * 0.5f - missile->getSize().x * 0.5f, getPosition().y };
        missile->setPosition(spawnPosition);
        mp_attackTime = Timer::getTime();
        break;
    }
}
