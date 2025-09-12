#include "GameManager.h"

#include "Enemy.h"
#include "Keyboard.h"
#include "Object.h"
#include "Obstacle.h"
#include "Player.h"
#include "Timer.h"
#include "UI.h"
#include "Window.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {}

void GameManager::start()
{
    std::srand(std::time(nullptr));

    unsigned int maxObstacleCount = static_cast<int>(mp_window->getDimensions().x * mp_window->getDimensions().y * 0.00005);
    unsigned int obstacleCount = std::rand() % maxObstacleCount;
    for (unsigned int i = 0; i < obstacleCount; i++)
    {
        createObject<Obstacle>();
    }
    
    unsigned int playerSpawnDelay = 1;
    unsigned int playerSpawnTimer = 0;

    while (mp_window->isOpen())
    {
        if (playerSpawnTimer == playerSpawnDelay)
        {
            mp_player = createObject<Player>();
        }
        
        // creating objects
        for (Object* pObject : mp_pendingObjectList)
        {
            mp_objectList.push_back(std::move(pObject));
        }
        mp_pendingObjectList.clear();

        // creating UI
        for (UI* pUI : mp_pendingUIList)
        {
            mp_uiList.push_back(std::move(pUI));
        }
        mp_pendingUIList.clear();

        // creating sprites
        for (Sprite* sprite : mp_pendingSpriteList)
        {
            mp_spriteList.push_back(std::move(sprite));
        }
        mp_pendingSpriteList.clear();

        // destroying objects
        for (Object* pObject : mp_objectToDestroy)
        {
            mp_objectList.erase(std::remove(mp_objectList.begin(), mp_objectList.end(), pObject), mp_objectList.end());
            delete pObject;
        }
        mp_objectToDestroy.clear();

        // destroying UI
        for (UI* pUI : mp_uiToDestroy)
        {
            mp_uiList.erase(std::remove(mp_uiList.begin(), mp_uiList.end(), pUI), mp_uiList.end());
            delete pUI;
        }
        mp_uiToDestroy.clear();

        // destroying sprites
        for (Sprite* sprite : mp_spriteToDestroy)
        {
            mp_spriteList.erase(std::remove(mp_spriteList.begin(), mp_spriteList.end(), sprite), mp_spriteList.end());
            delete sprite;
        }
        mp_spriteToDestroy.clear();

        // timer update
        mp_timer.update();
        if (mp_timer.getDelta() == 0.0f) continue;

        // window events
        mp_window->pollEvents();
        mp_window->setTitle("FPS: " + std::to_string(mp_timer.getFps()));

        // update objects
        updateObjects();

        // spawn enemies
        spawnEnemies();

        // check collisions
        checkCollisions();

        updateUI();

        // render
        mp_window->clear();
        render();
        mp_window->display();

        if (playerSpawnTimer <= playerSpawnDelay) playerSpawnTimer++;
    }
}

void GameManager::setWindow(Window* pWindow)
{
    mp_window = pWindow;
}

void GameManager::destroyObject(Object* object)
{
    if (std::find(mp_objectList.begin(), mp_objectList.end(), object) == mp_objectList.end() ||
        std::find(mp_objectToDestroy.begin(), mp_objectToDestroy.end(), object) != mp_objectToDestroy.end())
        return;
    if (object->isCollidingWith(mp_player))
    {
        mp_player->onCollisionExit(object);
    }
    mp_objectToDestroy.push_back(object);
}

void GameManager::destroyUI(UI* ui)
{
    if (std::find(mp_uiList.begin(), mp_uiList.end(), ui) == mp_uiList.end() ||
        std::find(mp_uiToDestroy.begin(), mp_uiToDestroy.end(), ui) != mp_uiToDestroy.end())
        return;
    mp_uiToDestroy.push_back(ui);
}

void GameManager::destroySprite(Sprite* sprite)
{
    if (std::find(mp_spriteList.begin(), mp_spriteList.end(), sprite) == mp_spriteList.end() ||
        std::find(mp_spriteToDestroy.begin(), mp_spriteToDestroy.end(), sprite) != mp_spriteToDestroy.end())
        return;
    
    mp_spriteToDestroy.push_back(sprite);
}

Window* GameManager::getWindow()
{
    return mp_window;
}

const std::vector<Object*>& GameManager::getObjects() const
{
    return mp_objectList;
}

void GameManager::render()
{
    for (Sprite* sprite : mp_spriteList)
    {
        mp_window->draw(*sprite);
    }

    /*for (Object* pObject : mp_objectList)
    {
        mp_window->draw(*pObject->mp_sprite);
    }

    for (UI* pUI : mp_uiList)
    {
        std::cout << "Rendering UI\n";
        mp_window->draw(*pUI->m_sprite);
    }*/
}

void GameManager::updateObjects()
{
    for (Object* pObject : mp_objectList)
    {
        pObject->update();
    }
}

void GameManager::updateUI()
{
    for (UI* pUI : mp_uiList)
    {
        pUI->update();
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

void GameManager::spawnEnemies()
{
    if (mp_enemyCount < 24)
    {
        if (std::rand() % 100 == 0)
        {
            createObject<Enemy>();
            addEnemies(1);
        }
    }
}

void GameManager::addEnemies(int count)
{
    mp_enemyCount += count;
}

void GameManager::checkCollisions()
{
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

            bool seenBefore = false;
            if (auto it = m_prevCollisions.find(a); it != m_prevCollisions.end())
                seenBefore = it->second.count(b) > 0;

            if (seenBefore)
            {
                a->onCollisionStay(b);
                b->onCollisionStay(a);
            }
            else
            {
                a->onCollisionEnter(b);
                b->onCollisionEnter(a);
            }

            curr[a].insert(b);
        }
    }

    for (auto& [a, setB] : m_prevCollisions)
    {
        if (!alive.count(a)) continue;
        for (Object* b : setB)
        {
            if (!alive.count(b)) continue;
            auto it = curr.find(a);
            const bool stillColliding = (it != curr.end()) && it->second.count(b);
            if (!stillColliding)
            {
                a->onCollisionExit(b);
                b->onCollisionExit(a);
            }
        }
    }

    m_prevCollisions.swap(curr);
}
