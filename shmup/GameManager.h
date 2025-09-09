#pragma once
#include <vector>

class Window;
class Keyboard;
class Timer;
class Object;
class Sprite;

class GameManager
{
public:
    GameManager();
    virtual ~GameManager(){}

    void start();
    void handleInput(Object* pObject);
    void setWindow(Window* pWindow);
    void setKeyboard(Keyboard* pKeyboard);
    void setTimer(Timer* pTimer);
    void subscribe(Sprite* pSprite);
    void render();
private:
    Window* mp_window;
    Keyboard* mp_keyboard;
    Timer* mp_timer;
    std::vector<Sprite*> mp_spriteList;
};
