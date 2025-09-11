#pragma once
#include "Sprite.h"
class GameManager;
class UI
{
public:
    UI();
    virtual ~UI() {}

    virtual void start();
    virtual void update() {}

protected:
    GameManager* mp_gameManager;
};
