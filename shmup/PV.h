#pragma once
#include "UI.h"

class PV : public UI
{
public:
    PV();
    virtual ~PV() {}
    void start() override;

private:
    Sprite* m_sprite2;
};
