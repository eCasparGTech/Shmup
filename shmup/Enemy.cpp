#include "Enemy.h"

#include "GameManager.h"
#include "Player.h"

Enemy::Enemy()
{
    m_state = idle;
}

void Enemy::update()
{
    Player* player = mp_gameManager->getPlayer();

    Alive::update();
    switch (m_state)
    {
    case idle:
        if (Object::getDistanceBetweenObjects(this, player) <= 100)
        {
            m_state = chasing;
        }
        else
        {
            m_state = wandering;
        }
        break;
    case wandering:
        if (Object::getDistanceBetweenObjects(this, player) <= 100)
        {
            m_state = chasing;
        }

        
        break;
    case chasing:
        
        break;
    case attacking:
        
        break;
    default:
        break;
    }
}

void Enemy::wander()
{
    switch (getRandomDirection())
    {
    case up:
        
        break;
    case down:
        
        break;
    case left:
        
        break;
    case right:
        
        break;
    default: ;
    }
}
