#include "Sprite.h"

void Sprite::init(Window window)
{
    window.subscribe(*this);
}
