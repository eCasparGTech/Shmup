#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <SFML/Graphics/Text.hpp>

#include "Keyboard.h"
#include "Player.h"

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
    void addEnemies(int count);
    void start();
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
    PV* m_pv = nullptr;
	AMMO* mp_ammo = nullptr;

private:
    Keyboard mp_keyboard;
    Timer mp_timer;
    Player* mp_player = nullptr;
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
    unsigned int mp_enemyCount = 0;
};
