#pragma once
#include <vector>

class Window;
class Sprite;
class Keyboard;
class Object;

class GameManager
{
public:
    GameManager();
    virtual ~GameManager(){}

    void start();
    void handleInput(Keyboard* pKeyboard, float deltaTime, Object* pObject);
    void subscribe(Sprite* pSprite);
    void setWindow(Window* pWindow);
    void render();
private:
    Window* mp_window;
    std::vector<Sprite*> mp_spriteList;
};
