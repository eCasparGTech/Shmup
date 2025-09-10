#pragma once
#include <vector>

#include "Player.h"

class Window;
class Keyboard;
class Timer;
class Object;
class Sprite;

class GameManager
{
    static GameManager *instance;
public:
    GameManager();
    virtual ~GameManager(){}

    void start();
    void setWindow(Window* pWindow);
    void setKeyboard(Keyboard* pKeyboard);
    void setTimer(Timer* pTimer);
    void subscribe(Object* pObject);
    void render();
    void updateObjects();
    Keyboard* getKeyboard();
    Timer* getTimer();
    Player* getPlayer();
    
    template <class T>
    T* createObject()
    {
        static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
        T* object = new T();
        mp_pendingObjectList.push_back(object);
        return object;
    }

    static GameManager *getInstance()
    {
        if (!instance)
            instance = new GameManager();
        return instance;
    }
private:
    Window* mp_window = nullptr;
    Keyboard* mp_keyboard = nullptr;
    Timer* mp_timer = nullptr;
    Player* mp_player = nullptr;
    std::vector<Object*> mp_objectList;
    std::vector<Object*> mp_pendingObjectList;
};
