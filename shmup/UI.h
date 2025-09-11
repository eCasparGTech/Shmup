#pragma once
#include "Sprite.h"

class UI
{
public:
    UI();
    virtual ~UI() {}

    virtual void start();
    virtual void update() {}

    Sprite* m_sprite;

protected:
    GameManager* mp_gameManager;
};
