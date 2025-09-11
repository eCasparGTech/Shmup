#include "Projectile.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Enemy.h"

#include "GameManager.h"

Projectile::Projectile() {}

static float length(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

void Projectile::start()
{
    Entity::start();
    setType(ObjectType::TProjectile);
    m_moveSpeed = 500.0f;
    mp_birthtime = Timer::getTime();
    mp_lifetime = 5.0f;

    mp_gameManager = GameManager::getInstance();
    Player* player = mp_gameManager->getPlayer();
    Object* nearest = nullptr;
    float nearestDistance = 0.0f;
    for (Object* object : mp_gameManager->getObjects())
    {
        if (object->getType() == TEnemy)
        {
            sf::Vector2f enemyDifference = object->getPosition() - player->m_position;
            float distance = length(enemyDifference);
            if (nearest == nullptr || distance < nearestDistance)
            {
                nearest = object;
                nearestDistance = distance;
            }
        }
    }
    
    sf::Vector2f projectileDifference = nearest->getPosition() - player->m_position;
    float max = std::max(abs(projectileDifference.x), abs(projectileDifference.y));
    mp_direction = { projectileDifference.x / max, projectileDifference.y / max };

    float pi = 3.14159265358979323846f;
    
    float angleRad = std::atan2(projectileDifference.x, -projectileDifference.y);
    float angleDeg = angleRad * 180.f / static_cast<float>(pi);

    mp_sprite->setRotation(angleDeg);
}

void Projectile::update()
{
    Entity::update();
    move(mp_direction);

    float age = Timer::getTime() - mp_birthtime;
    if (age >= mp_lifetime) mp_gameManager->destroyObject(this);
}
