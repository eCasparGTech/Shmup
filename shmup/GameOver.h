#pragma once
#include "UI.h"

class GameOver: public UI
{
public:
    GameOver();
    virtual ~GameOver() {};

    virtual void start() override;

    void displayGameOver();
    
};
