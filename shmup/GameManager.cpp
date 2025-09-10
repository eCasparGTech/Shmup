#include "GameManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Keyboard.h"
#include "Object.h"
#include "Player.h"
#include "Sprite.h"
#include "Timer.h"
#include "Window.h"

GameManager *GameManager::instance = nullptr;

GameManager::GameManager()
{
    
}

void GameManager::start()
{
    Keyboard keyboard = Keyboard();
    setKeyboard(&keyboard);
    
    Timer timer = Timer();
    setTimer(&timer);
    
    //Player player = Player();
    //Object object = Object();
    createObject<Player>();
    
    while (mp_window->isOpen())
    {
        
        mp_window->pollEvents();
        
        mp_timer->update();
        if (mp_timer->getDelta() == 0.0f) continue;
        
        mp_window->setTitle("FPS: " + std::to_string(mp_timer->getFps()));

        updateObjects();
        
        // render
        mp_window->clear();
        render();
        mp_window->display();
        
        //mp_objectList.clear();
        
        for (Object* pObject : mp_pendingObjectList)
        {
            mp_objectList.push_back(std::move(pObject));
        }
        mp_pendingObjectList.clear();
    }
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

void GameManager::subscribe(Object* pObject)
{
    mp_pendingObjectList.push_back(pObject);
}

void GameManager::render()
{
    for (Object* pObject : mp_objectList)
    {
        mp_window->draw(*pObject->mp_sprite);
    }
}

void GameManager::updateObjects()
{
    for (Object* pObject : mp_objectList)
    {
        pObject->update();
    }
}

Keyboard* GameManager::getKeyboard()
{
    return mp_keyboard;
}

Timer* GameManager::getTimer()
{
    return mp_timer;
}

Player* GameManager::getPlayer()
{
    return mp_player;
}
