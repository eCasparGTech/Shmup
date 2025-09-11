#include "Alive.h"

#include "GameManager.h"
#include "Missile.h"

Alive::Alive() {}

void Alive::start()
{
    Entity::start();
    mp_attackTime = 0.0f;
    mp_attackCooldown = 0.05f;

    m_hitActive = false;
    m_hitUntil  = 0.0f;
}

void Alive::update()
{
    Entity::update();

    if (m_hitActive)
    {
        float now = Timer::getTime();
        if (now >= m_hitUntil)
        {
            mp_sprite->setColor(mp_sprite->baseColor);
            m_hitActive = false;
        }
    }
}

void Alive::Attack(AttackType attackType)
{
    switch (attackType)
    {
    case Projectile:
        if (Timer::getTime() - mp_attackTime < mp_attackCooldown) break;
        Missile* missile = mp_gameManager->createObject<Missile>();
        sf::Vector2f spawnPosition = getPosition() + getSize() * 0.5f - missile->getSize() * 0.5f;
        missile->setPosition(spawnPosition);
        mp_attackTime = Timer::getTime();
        break;
    }
}

void Alive::takeDamage(int damage)
{
    mp_life -= damage;

    mp_sprite->setColor({255, 0, 0, 255});
    m_hitActive = true;
    m_hitUntil  = Timer::getTime() + 0.12f;
    
    if (mp_life <= 0)
    {
        mp_life = 0;
        die();
    }
}

void Alive::die()
{
    mp_gameManager->destroyObject(this);
}
