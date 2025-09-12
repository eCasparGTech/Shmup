#pragma once
#include "UI.h"

class Score : public UI
{
public:
    Score();
    virtual ~Score() {}

    void start() override;
    void updateScore();

    Sprite* mp_scoreText;
};
