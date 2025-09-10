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
    
    createObject<Player>();
    
    while (mp_window->isOpen())
    {
        // creating objects
        for (Object* pObject : mp_pendingObjectList)
        {
            mp_objectList.push_back(std::move(pObject));
        }
        mp_pendingObjectList.clear();

        // destroying objects
        for (Object* pObject : mp_objectToDestroy)
        {
            mp_objectList.erase(std::remove(mp_objectList.begin(), mp_objectList.end(), pObject), mp_objectList.end());
            delete pObject;
        }
        mp_objectToDestroy.clear();

        // timer update
        mp_timer->update();
        if (mp_timer->getDelta() == 0) continue;

        // window events
        mp_window->pollEvents();
        mp_window->setTitle("FPS: " + std::to_string(mp_timer->getFps()));

        // update objects
        updateObjects();
        
        // render
        mp_window->clear();
        render();
        mp_window->display();
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

void GameManager::destroyObject(Object* object)
{
    if (std::find(mp_objectList.begin(), mp_objectList.end(), object) == mp_objectList.end()) return;
    mp_objectToDestroy.push_back(object);
}

Window* GameManager::getWindow()
{
    return mp_window;
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
