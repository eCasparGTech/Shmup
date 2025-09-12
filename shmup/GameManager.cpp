#include "GameManager.h"

#include "Enemy.h"
#include "GameOver.h"
#include "Keyboard.h"
#include "Object.h"
#include "ObjectType.h"
#include "Obstacle.h"
#include "Player.h"
#include "PV.h"
#include "Timer.h"
#include "UI.h"
#include "Window.h"
#include "Score.h"

class Score;
GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {}

void GameManager::start()
{
    std::srand(std::time(nullptr));

    unsigned int maxObstacleCount = static_cast<int>(mp_window->getDimensions().x * mp_window->getDimensions().y *
        0.00005);
    unsigned int obstacleCount = std::rand() % maxObstacleCount;
    for (unsigned int i = 0; i < obstacleCount; i++)
    {
        createObject<Obstacle>();
    }
    
    unsigned int playerSpawnDelay = 1;
    unsigned int playerSpawnTimer = 0;

    unsigned int waveSpawnDelay = 3000;
    mp_waveSpawnTimer = 0;
    mp_waveEnnemies = 10;
    
    while (mp_window->isOpen())
    {
        if (playerSpawnTimer == playerSpawnDelay)
        {
            m_pv = createUI<PV>();
            mp_ammo = createUI<AMMO>();
            m_gameOver = createUI<GameOver>();
            mp_player = createObject<Player>();
            mp_score = createUI<Score>();
        }

        if (mp_waveSpawnTimer == waveSpawnDelay)
        {
            mp_allowEnemies = true;
        }

        // restart game
        if (mp_player == nullptr && mp_keyboard.keyRelease(KeyCode::enter))
        {
            restartGame();
            playerSpawnTimer = 0;
            mp_waveSpawnTimer = 0;
            mp_allowEnemies = true;
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
            if (pObject->getType() == TPlayer)
            {
                mp_player = nullptr;
            }
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

        // keyboard update
        mp_keyboard.update();

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

void GameManager::restartGame()
{
    mp_allowEnemies = false;

    for (Object* pObject : mp_objectList) delete pObject;
    mp_objectList.clear();
    mp_objectToDestroy.clear();

    for (UI* pUI : mp_uiList) delete pUI;
    mp_uiList.clear();
    mp_uiToDestroy.clear();

    for (Sprite* sprite : mp_spriteList) delete sprite;
    mp_spriteList.clear();
    mp_spriteToDestroy.clear();

    mp_pendingObjectList.clear();
    mp_pendingUIList.clear();
    mp_pendingSpriteList.clear();

    m_prevCollisions.clear();
    mp_player = nullptr;
    m_enemyCount = 0;
    mp_scoreValue = 0;

    const auto dims = mp_window->getDimensions();
    unsigned int maxObstacleCount =
        static_cast<unsigned int>(dims.x * dims.y * 0.00005f);
    if (maxObstacleCount == 0) maxObstacleCount = 1;
    unsigned int obstacleCount = std::rand() % maxObstacleCount;
    for (unsigned int i = 0; i < obstacleCount; ++i)
    {
        createObject<Obstacle>();
    }

    m_wave = 0;
    mp_waveEnnemies = 10;
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
    if (mp_allowEnemies && m_enemyCount < 24 && mp_ennemiesSpawnedInWave < mp_waveEnnemies)
    {
        if (std::rand() % 100 == 0)
        {
            createObject<Enemy>();
            addEnemies();
        }
    }
    if (m_enemyCount == 0 && mp_ennemiesSpawnedInWave == mp_waveEnnemies)
    {
        mp_allowEnemies = false;
        nextWave();
    }
}

void GameManager::nextWave()
{
    m_wave++;
    mp_ennemiesSpawnedInWave = 0;
    mp_waveSpawnTimer = 0;
}

int GameManager::waveEnemyCount(int waveNumber)
{
    if (waveNumber <= 1)  return 10;
    if (waveNumber >= 100) return 1000;

    int num = (1000 - 14) * (waveNumber - 2);
    return 14 + (num + 98 / 2) / 98;
}

void GameManager::addEnemies()
{
    m_enemyCount++;
    mp_ennemiesSpawnedInWave++;
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
