#pragma once
#include "Alive.h"

class Keyboard;

class Player : public Alive
{
public:
    Player();
    virtual ~Player(){}

    void start() override;
    void update() override;
    void onCollisionEnter(Object* other) override;
    void onCollisionExit(Object* other) override;
    void handleInput();

private:
    Keyboard* keyboard;
};
