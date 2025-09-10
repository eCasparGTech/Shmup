#include "Player.h"

#include "GameManager.h"
#include "Keyboard.h"
#include "Timer.h"

void Player::handleInput()
{
    Keyboard* keyboard = mp_gameManager->getKeyboard();
    keyboard->update();
    
    float moveSpeed = 0.2f;
    sf::Vector2f distance = {0.0f, 0.0f};

    if (keyboard->keyDown(KeyCode::up))
    {
        distance.y -= moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::down))
    {
        distance.y += moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::right))
    {
        distance.x += moveSpeed;
    }

    if (keyboard->keyDown(KeyCode::left))
    {
        distance.x -= moveSpeed;
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

Player::Player()
{
    
}

void Player::update()
{
    Alive::update();
    handleInput();
}
