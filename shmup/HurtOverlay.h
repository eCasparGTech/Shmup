#pragma once
#include "UI.h"

class HurtOverlay : public UI
{
public:
    HurtOverlay();
    virtual ~HurtOverlay() {};

    virtual void start() override;

    void showHurtOverlay();
    void hideHurtOverlay();

private:
    Sprite* mp_hurtOverlay = nullptr;
};
