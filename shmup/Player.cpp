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
    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    setSize({15.0f, 15.0f});
    mp_sprite->baseColor = {0, 0, 200, 255};
    mp_sprite->setColor(mp_sprite->baseColor);
    setPosition({dimensions.x * 0.5f, dimensions.y * 0.5f});
    keyboard = mp_gameManager->getKeyboard();
    m_aimDirection = { 0.0f, -1.0f };
    m_aimAngle = 0.0f;

    mp_pv = mp_gameManager->createUI<PV>();
    heal(3);
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
        Attack(Projectile);
    }

    move(distance);
}

void Player::heal(int amount)
{
    Alive::heal(amount);
    mp_pv->setLife(mp_life);
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
