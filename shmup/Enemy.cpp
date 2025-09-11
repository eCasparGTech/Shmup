#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"
#include "Window.h"
#include "Timer.h"

static float vlen(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Enemy::Enemy() {}

void Enemy::start()
{
    Alive::start();
    setType(ObjectType::TEnemy);

    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    setPosition({dimensions.x * 0.5f, dimensions.y * 0.1f});
    setSize({15.0f, 15.0f});
    mp_sprite->baseColor = {0, 150, 0, 255};
    mp_sprite->setColor(mp_sprite->baseColor);
    m_movingState = idle;
    m_moveSpeed = 100.0f;

    mp_player = mp_gameManager->getPlayer();

    m_sleeping = false;
    m_sleepTime = 0.0f;
    m_sleepDuration = 0.0f;

    m_attacking = false;
    m_charging = false;
    m_releasing = false;

    // Anti-stuck: init
    m_unstuckActive = false;
    m_unstuckUntil = 0.0f;

    setStuckParams(1.0f, 4.0f);

    m_attackStartPos = m_position;
    m_attackChargeStartTime = 0.0f;
    m_minMoveBeforeDash = 4.0f;
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

    if (m_unstuckActive)
    {
        if (Timer::getTime() >= m_unstuckUntil)
        {
            m_unstuckActive = false;
        }
        else
        {
            return;
        }
    }

    // anti-stuck
    if (isStuck())
    {
        if (m_attacking || m_charging || m_releasing)
        {
            m_attacking = false;
            m_charging = false;
            m_releasing = false;
            m_moveSpeed = 100.0f;
            m_hasDestination = false;
        }

        resetStuckProbe();

        m_unstuckActive = true;
        m_unstuckUntil = Timer::getTime() + 0.6f;

        if (m_movingState == chasing && mp_player)
        {
            sf::Vector2f toPlayer = mp_player->m_position - m_position;
            sf::Vector2f perp = {-toPlayer.y, toPlayer.x};
            float len = vlen(perp);
            if (len > 1e-4f)
            {
                sf::Vector2f dir = {perp.x / len, perp.y / len};
                float side = (std::rand() % 2 == 0) ? 1.f : -1.f;
                setDestination(m_position + dir * side * 160.f);
            }
            else
            {
                wander();
            }
        }
        else
        {
            wander();
        }
        return;
    }

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
                if (!isStuck() && !m_unstuckActive)
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

void Enemy::onCollisionEnter(Object* other)
{
    Alive::onCollisionEnter(other);
    if (other->getType() == ObjectType::TProjectile)
    {
        takeDamage(1);
    }
}
