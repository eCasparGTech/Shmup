#include "Player.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Projectile.h"
#include "Window.h"

Player::Player()
{
    setType(ObjectType::TPlayer);
    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    setPosition({dimensions.x * 0.5f, dimensions.y * 0.5f});
    setSize({80.0f, 80.0f});
    mp_sprite->setColor({0, 0, 200, 255});
}

void Player::handleInput()
{
    Keyboard* keyboard = mp_gameManager->getKeyboard();
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

    /*if (keyboard->keyPress(KeyCode::space))
    {
        sf::Vector2f destination = {200.0f, 200.0f};
        setDestination(&destination);
    }*/

    /*if (m_hasDestination)
    {
        goToDestination();
    }*/
}

void Player::update()
{
    Alive::update();
    handleInput();
}

void Player::onCollisionEnter(Object* other)
{
    std::cout << "Collision with " << other->getType() << std::endl;
    if (other->getType() == ObjectType::TObstacle)
    {
        mp_sprite->setColor({255, 0, 0, 255});
    } else
    {
        mp_sprite->setColor({0, 0, 200, 255});
    }
}
