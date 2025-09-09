#include "Player.h"

#include "GameManager.h"
#include "Keyboard.h"
#include "Timer.h"

void Player::handleInput()
{
    Keyboard* keyboard = mp_gameManager->getKeyboard();
    keyboard->update();

    Timer* timer = mp_gameManager->getTimer();
    
    float moveSpeed = 0.2f;
    float speed = moveSpeed * timer->getDelta();
    sf::Vector2f distance = {0.0f, 0.0f};

    if (keyboard->keyDown(KeyCode::up))
    {
        distance.y -= speed;
    }

    if (keyboard->keyDown(KeyCode::down))
    {
        distance.y += speed;
    }

    if (keyboard->keyDown(KeyCode::right))
    {
        distance.x += speed;
    }

    if (keyboard->keyDown(KeyCode::left))
    {
        distance.x -= speed;
    }
    
    move(distance);
}

Player::Player()
{
    
}

void Player::update()
{
    Object::update();
    handleInput();
}
