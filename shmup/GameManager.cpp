#include "GameManager.h"
#include "Keyboard.h"
#include "Object.h"
#include "Obstacle.h"
#include "Player.h"
#include "Timer.h"
#include "Window.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {}

void GameManager::start()
{
    //Keyboard keyboard;
    //setKeyboard(&keyboard);

    Timer timer = Timer();

    createObject<Player>();
    createObject<Obstacle>();

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
        mp_timer.update();
        if (mp_timer.getDelta() == 0) continue;

        // window events
        mp_window->pollEvents();
        mp_window->setTitle("FPS: " + std::to_string(mp_timer.getFps()));

        // update objects
        updateObjects();

        // check collisions
        checkCollisions();
        
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
    return &mp_keyboard;
}

Timer* GameManager::getTimer()
{
    return &mp_timer;
}

Player* GameManager::getPlayer()
{
    return mp_player;
}

void GameManager::checkCollisions()
{
    // Par sécurité: ignorer les objets détruits (si destruction a eu lieu avant cette étape)
    std::unordered_set<Object*> alive(mp_objectList.begin(), mp_objectList.end());

    std::unordered_map<Object*, std::unordered_set<Object*>> curr;

    const size_t n = mp_objectList.size();
    for (size_t i = 0; i < n; ++i)
    {
        Object* a = mp_objectList[i];
        for (size_t j = i + 1; j < n; ++j)
        {
            Object* b = mp_objectList[j];

            if (!a->isCollidingWith(b)) continue;

            // Était-ce déjà en collision à la frame précédente ? (on ne stocke que a->b)
            bool seenBefore = false;
            if (auto it = m_prevCollisions.find(a); it != m_prevCollisions.end())
                seenBefore = it->second.count(b) > 0;

            if (seenBefore) {
                a->onCollisionStay(b);
                b->onCollisionStay(a);
            } else {
                a->onCollisionEnter(b);
                b->onCollisionEnter(a);
            }

            curr[a].insert(b); // On ne stocke QUE a->b (i<j), jamais b->a
        }
    }

    for (auto& [a, setB] : m_prevCollisions)
    {
        if (!alive.count(a)) continue; // a détruit
        for (Object* b : setB)
        {
            if (!alive.count(b)) continue; // b détruit
            auto it = curr.find(a);
            const bool stillColliding = (it != curr.end()) && it->second.count(b);
            if (!stillColliding) {
                a->onCollisionExit(b);
                b->onCollisionExit(a);
            }
        }
    }

    m_prevCollisions.swap(curr);
}