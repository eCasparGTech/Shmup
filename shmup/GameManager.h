#pragma once
#include <vector>

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
    std::vector<Object*> mp_objectList;
};
