#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "HurtOverlay.h"
#include "Keyboard.h"
#include "Player.h"
#include "Score.h"
#include "WaveNumber.h"

class Score;
class PV;
class GameOver;
class UI;
class Window;
class Keyboard;
class Timer;
class Object;
class Sprite;

class GameManager
{
    static GameManager* instance;

public:
    GameManager();
    virtual ~GameManager() {}

    void spawnEnemies();
    void nextWave();
    int waveEnemyCount(int waveNumber);
    void addEnemies();
    void start();
    void restartGame();
    void setWindow(Window* pWindow);
    void render();
    void updateObjects();
    void updateUI();
    Keyboard* getKeyboard();
    Timer* getTimer();
    Player* getPlayer();
    void checkCollisions();
    void destroyObject(Object* object);
    void destroyUI(UI* ui);
    void destroySprite(Sprite* sprite);
    Window* getWindow();
    const std::vector<Object*>& getObjects() const;

    Sprite* createSprite()
    {
        Sprite* sprite = new Sprite();
        mp_pendingSpriteList.push_back(sprite);
        sprite->start();
        return sprite;
    }

    template <class T>
    T* createObject()
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
        T* object = new T();
        mp_pendingObjectList.push_back(object);
        object->start();
        return object;
    }

    template <class T>
    T* createUI()
    {
        static_assert(std::is_base_of<UI, T>::value, "T must derive from Object");
        T* ui = new T();
        mp_pendingUIList.push_back(ui);
        ui->start();
        return ui;
    }

    static GameManager* getInstance()
    {
        if (instance == nullptr)
            instance = new GameManager();
        return instance;
    }

    Window* mp_window = nullptr;
    GameOver* m_gameOver = nullptr;
    WaveNumber* m_waveNumber = nullptr;
    HurtOverlay* m_hurtOverlay = nullptr;
    PV* m_pv = nullptr;
	AMMO* mp_ammo = nullptr;

    void setScore(int score)
    {
        mp_scoreValue = score;
        mp_score->updateScore();
    }

    void addScore(int score)
    {
        mp_scoreValue += score;
        mp_score->updateScore();
    }

    int getScore() { return mp_scoreValue; }
    
    unsigned int m_enemyCount = 0;
    int m_wave = 0;
private:
    Keyboard mp_keyboard;
    Timer mp_timer;
    Player* mp_player = nullptr;
    Score* mp_score = 0;
    int mp_scoreValue = 0;
    std::vector<Object*> mp_objectList;
    std::vector<Object*> mp_pendingObjectList;
    std::vector<Object*> mp_objectToDestroy;
    std::unordered_map<Object*, std::unordered_set<Object*>> m_prevCollisions;

    std::vector<UI*> mp_uiList;
    std::vector<UI*> mp_pendingUIList;
    std::vector<UI*> mp_uiToDestroy;

    std::vector<Sprite*> mp_spriteList;
    std::vector<Sprite*> mp_pendingSpriteList;
    std::vector<Sprite*> mp_spriteToDestroy;
    bool mp_allowEnemies = false;
    
    int mp_waveEnnemies = 0;
    int mp_ennemiesSpawnedInWave = 0;
    int mp_waveSpawnTimer = 0;
};
