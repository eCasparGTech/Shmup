#include "GameManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Keyboard.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Window.h"

GameManager::GameManager()
{
    
}

void GameManager::start()
{
    Keyboard keyboard = Keyboard();
    setKeyboard(&keyboard);
    
    Timer timer = Timer();
    setTimer(&timer);
    
    Object object = Object();
    object.setGameManager(this);
    
    while (mp_window->isOpen())
    {
        mp_window->pollEvents();
        
        mp_timer->update();
        if (mp_timer->getDelta() == 0.0f) continue;
        
        mp_window->setTitle("FPS: " + std::to_string(mp_timer->getFps()));

        handleInput(&object);
        
        // render
        mp_window->clear();
        render();
        mp_window->display();
    }
}

void GameManager::handleInput(Object* pObject)
{
    mp_keyboard->update();
    float moveSpeed = 0.2f;
    float speed = moveSpeed * mp_timer->getDelta();
    sf::Vector2f distance = {0.0f, 0.0f};

    if (mp_keyboard->keyDown(KeyCode::up))
    {
        distance.y -= speed;
    }

    if (mp_keyboard->keyDown(KeyCode::down))
    {
        distance.y += speed;
    }

    if (mp_keyboard->keyDown(KeyCode::right))
    {
        distance.x += speed;
    }

    if (mp_keyboard->keyDown(KeyCode::left))
    {
        distance.x -= speed;
    }
    
    pObject->move(distance);
}

void GameManager::setWindow(Window* pWindow)
{
    mp_window = pWindow;
}

void GameManager::setKeyboard(Keyboard* pKeyboard)
{
    mp_keyboard = pKeyboard;
}

void GameManager::setTimer(Timer* pTimer)
{
    mp_timer = pTimer;
}

void GameManager::subscribe(Sprite* pSprite)
{
    mp_spriteList.push_back(pSprite);
}

void GameManager::render()
{
    for (Sprite* pSprite : mp_spriteList)
    {
        mp_window->draw(*pSprite);
    }
}
