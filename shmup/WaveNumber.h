#pragma once
#include "UI.h"

class WaveNumber : public UI
{
public:
    WaveNumber();
    virtual ~WaveNumber() {};
    
    virtual void start() override;

    void showWaveNumber();
    void hideWaveNumber();

private:
    Sprite* mp_waveNumberText = nullptr;
};
