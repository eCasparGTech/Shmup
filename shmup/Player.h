#pragma once
#include "Alive.h"

class Player : public Alive
{
public:
    Player();
    virtual ~Player(){}

    void update() override;
    void handleInput();
};
