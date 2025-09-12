#pragma once
#include "UI.h"

class WaveNumber : public UI
{
public:
    WaveNumber();
    virtual ~WaveNumber() {};
    
    virtual void start() override;
    
    void displayWaveNumber();
};
