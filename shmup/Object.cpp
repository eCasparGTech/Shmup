#include "Object.h"
#include "GameManager.h"
#include "Keyboard.h"
#include "Timer.h"

Object::Object()
{
    mp_sprite = new Sprite();
    mp_gameManager = GameManager::getInstance();
}

void Object::update()
{
    handleInput();
}

void Object::handleInput()
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

void Object::move(sf::Vector2f distance)
{
    m_position += distance;
    mp_sprite->setPosition(m_position);
}

/*
void Object::rotate(float rotation)
{
    m_rotation += rotation;
}

void Object::scale(float width, float height)
{
    m_width += width;
    m_height += height;
}
*/

void Object::setGameManager(GameManager* manager)
{
    manager->subscribe(this);
}
