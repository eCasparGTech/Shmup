#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"
#include "Window.h"

Enemy::Enemy() {}

void Enemy::start()
{
    Alive::start();
    setType(ObjectType::TEnemy);
    
    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    setPosition({dimensions.x * 0.5f, dimensions.y * 0.1f});
    setSize({80.0f, 80.0f});
    mp_sprite->setColor({0, 200, 0, 255});
    m_movingState = idle;
    m_moveSpeed = 100.0f;

    mp_player = mp_gameManager->getPlayer();

    m_sleeping = false;
    m_sleepTime = 0.0f;
    m_sleepDuration = 0.0f;

    m_attacking = false;
    m_charging = false;
    m_releasing = false;
}

void Enemy::update()
{
    Alive::update();
    
    if (mp_player == nullptr)
    {
        mp_player = mp_gameManager->getPlayer();
        return;
    }
    
    if (m_destinationReached)
    {
        m_destinationReached = false;
        if (m_attacking && m_releasing)
        {
            m_attacking = false;
            m_charging = false;
            m_releasing = false;
            m_moveSpeed = 100.0f;
        }
        if (m_sleeping == false && m_sleepDuration > 0.0f)
        {
            m_sleeping = true;
            m_sleepTime = Timer::getTime();
        }
    }

    if (m_sleeping && Timer::getTime() - m_sleepTime >= m_sleepDuration)
    {
        m_sleepDuration = 0.0f;
        m_sleeping = false;
    }
    if (m_sleeping) return;

    // Attack update
    if (m_attacking)
    {
        if (m_charging == false && m_releasing == false)
        {
            m_hasDestination = false;
            m_destinationReached = true;
            m_sleepDuration = 0.4f;
            m_charging = true;
        }
        else if (m_charging && m_releasing == false)
        {
            m_releasing = true;
            m_charging = false;
            m_sleepDuration = 1.2f;
            attack();
        }
    }
    else
    {
        // Enemy movement
        switch (m_movingState)
        {
        case idle:
            if (getDistance(this, mp_player) <= 160)
            {
                m_hasDestination = false;
                m_movingState = chasing;
            }
            else
            {
                m_movingState = wandering;
            }
            break;
        case wandering:
            if (getDistance(this, mp_player) <= 160)
            {
                m_hasDestination = false;
                m_movingState = chasing;
                break;
            }
            if (!m_hasDestination) wander();
            break;
        case chasing:
            if (getDistance(this, mp_player) <= 80)
            {
                m_attacking = true;
                break;
            }
            if (getDistance(this, mp_player) > 320)
            {
                m_movingState = wandering;
                break;
            }
            setDestination(mp_player->m_position);
            break;
        }
    }
}

void Enemy::wander()
{
    sf::Vector2f destination = {m_position.x, m_position.y};
    switch (getRandomDirection())
    {
    case up:
        destination.y -= 160.0f;
        break;
    case down:
        destination.y += 160.0f;
        break;
    case left:
        destination.x -= 160.0f;
        break;
    case right:
        destination.x += 160.0f;
        break;
    }
    setDestination(destination);
    m_sleepDuration = static_cast<float>((std::rand() % 3000) * 0.001);
}

void Enemy::attack()
{
    m_moveSpeed *= 3;
    setDestination(mp_player->m_position);
}
