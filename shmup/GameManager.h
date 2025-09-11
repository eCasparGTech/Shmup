#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Keyboard.h"
#include "Player.h"

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

    void start();
    void setWindow(Window* pWindow);
    void subscribe(Object* pObject);
    void render();
    void updateObjects();
    Keyboard* getKeyboard();
    Timer* getTimer();
    Player* getPlayer();
    void checkCollisions();
    void destroyObject(Object* object);
    Window* getWindow();

    template <class T>
    T* createObject()
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
        T* object = new T();
        mp_pendingObjectList.push_back(object);
        object->start();
        return object;
    }

    static GameManager* getInstance()
    {
        if (instance == nullptr)
            instance = new GameManager();
        return instance;
    }

private:
    Window* mp_window = nullptr;
    Keyboard mp_keyboard;
    Timer mp_timer;
    Player* mp_player = nullptr;
    std::vector<Object*> mp_objectList;
    std::vector<Object*> mp_pendingObjectList;
    std::vector<Object*> mp_objectToDestroy;
    std::unordered_map<Object*, std::unordered_set<Object*>> m_prevCollisions;
};
