#include "Player.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Projectile.h"
#include "PV.h"
#include "Window.h"

Player::Player() {}

void Player::start()
{
    Alive::start();
    setType(ObjectType::TPlayer);
    setSize({15.0f, 15.0f});
    mp_sprite->baseColor = {0, 0, 200, 255};
    mp_sprite->setColor(mp_sprite->baseColor);

    sf::Vector2u dimensionsInt = mp_gameManager->getWindow()->getDimensions();
    sf::Vector2f dimensions = {static_cast<float>(dimensionsInt.x), static_cast<float>(dimensionsInt.y)};

    float randomX = ((std::rand() % 801) + 100) * 0.001f;
    float randomY = ((std::rand() % 801) + 100) * 0.001f;
    sf::Vector2f position = {dimensions.x * randomX, dimensions.y * randomY};
    setPosition(position);

    while (isCollidingWithAnyObstacle())
    {
        randomX = ((std::rand() % 801) + 100) * 0.001f;
        randomY = ((std::rand() % 801) + 100) * 0.001f;
        position = {dimensions.x * randomX, dimensions.y * randomY};
        setPosition(position);
    }

    keyboard = mp_gameManager->getKeyboard();
    m_aimDirection = {0.0f, -1.0f};
    m_aimAngle = 0.0f;

    mp_pv = mp_gameManager->createUI<PV>();
    heal(3);
    mp_ammo = mp_gameManager->createUI<AMMO>();
    giveAmmo(200);
}

void Player::handleInput()
{
    keyboard->update();

    sf::Vector2f distance = {0.0f, 0.0f};

    if (keyboard->keyDown(KeyCode::up))
    {
        distance.y -= 1;
    }

    if (keyboard->keyDown(KeyCode::down))
    {
        distance.y += 1;
    }

    if (keyboard->keyDown(KeyCode::right))
    {
        distance.x += 1;
    }

    if (keyboard->keyDown(KeyCode::left))
    {
        distance.x -= 1;
    }

    if (keyboard->keyDown(KeyCode::space))
    {
        if (mp_ammoCount > 0)
        {
            bool attackSuccess = tryAttack(Projectile);
            if (attackSuccess)
            {
                mp_ammoCount--;
                mp_ammo->setAmmo(mp_ammoCount);
            }
        }
    }

    move(distance);
}

void Player::heal(int amount)
{
    Alive::heal(amount);
    mp_pv->setLife(mp_life);
}

void Player::giveAmmo(int amount)
{
    unsigned int ammoCount = mp_ammoCount + amount;
    if (ammoCount > 800) ammoCount = 800;
    mp_ammoCount = ammoCount;
    mp_ammo->setAmmo(ammoCount);
}

void Player::takeDamage(int damage)
{
    Alive::takeDamage(damage);

    std::cout << "Take damage" << std::endl;

    mp_pv->setLife(mp_life);
}

void Player::update()
{
    Alive::update();
    handleInput();
}

void Player::onCollisionEnter(Object* other)
{
    Alive::onCollisionEnter(other);

    if (other->getType() == ObjectType::TEnemy)
    {
        mp_sprite->setColor({255, 0, 0, 255});
        takeDamage(1);
    }
}

void Player::onCollisionExit(Object* other)
{
    Alive::onCollisionExit(other);

    if (other->getType() == ObjectType::TEnemy)
    {
        mp_sprite->setColor(mp_sprite->baseColor);
    }
}
