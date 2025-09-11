#include "Player.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Projectile.h"
#include "Window.h"

Player::Player() {}

void Player::start()
{
    Alive::start();
    setType(ObjectType::TPlayer);
    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    setSize({15.0f, 15.0f});
    mp_sprite->setColor({0, 0, 200, 255});
    setPosition({dimensions.x * 0.5f, dimensions.y * 0.5f});
    keyboard = mp_gameManager->getKeyboard();
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
    }
}

void Player::onCollisionExit(Object* other)
{
    Alive::onCollisionExit(other);

    if (other->getType() == ObjectType::TEnemy)
    {
        mp_sprite->setColor({0, 0, 200, 255});
    }
}
