#include "Player.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Missile.h"
#include "Projectile.h"
#include "Window.h"

Player::Player()
{
    sf::Vector2u dimensions = mp_gameManager->getWindow()->getDimensions();
    m_position = { dimensions.x * 0.5f, dimensions.y * 0.5f };
}

void Player::handleInput()
{
    Keyboard* keyboard = mp_gameManager->getKeyboard();
    keyboard->update();

    sf::Vector2f distance = {0.0f, 0.0f};

    if (keyboard->keyDown(KeyCode::up))
    {
        distance.y -= m_moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::down))
    {
        distance.y += m_moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::right))
    {
        distance.x += m_moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::left))
    {
        distance.x -= m_moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::space))
    {
        Attack(Projectile);
    }

    /*if (keyboard->keyPress(KeyCode::space))
    {
        sf::Vector2f destination = {200.0f, 200.0f};
        setDestination(&destination);
    }*/

    /*if (m_hasDestination)
    {
        goToDestination();
    }*/

    move(&distance);
}

void Player::update()
{
    Alive::update();
    handleInput();
}
