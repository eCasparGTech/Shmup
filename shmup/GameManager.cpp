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
    Timer timer;

    Keyboard keyboard;
    
    Object object = Object();
    object.setGameManager(this);
    
    while (mp_window->isOpen())
    {
        timer.update();

        float deltaTime = static_cast<float>(timer.m_deltaTime);

        if (deltaTime == 0.f) continue;
        
        float seconds = deltaTime * 0.001f;
        float fps = 1 / seconds;

        handleInput(&keyboard, deltaTime, &object);
        
        // render
        mp_window->clear();
        render();
        mp_window->display();
    }
}

void GameManager::handleInput(Keyboard* pKeyboard, float deltaTime, Object* pObject)
{
    pKeyboard->update();
    float moveSpeed = 0.2f;
    float speed = moveSpeed * deltaTime;
    sf::Vector2f distance = {0.0f, 0.0f};

    if (pKeyboard->keyDown(KeyCode::up))
    {
        distance.y -= speed;
    }

    if (pKeyboard->keyDown(KeyCode::down))
    {
        distance.y += speed;
    }

    if (pKeyboard->keyDown(KeyCode::right))
    {
        distance.x += speed;
    }

    if (pKeyboard->keyDown(KeyCode::left))
    {
        distance.x -= speed;
    }
    
    pObject->move(distance);
}


void GameManager::subscribe(Sprite* pSprite)
{
    mp_spriteList.push_back(pSprite);
}

void GameManager::setWindow(Window* pWindow)
{
    mp_window = pWindow;
}

void GameManager::render()
{
    for (Sprite* pSprite : mp_spriteList)
    {
        mp_window->draw(*pSprite);
    }
}
