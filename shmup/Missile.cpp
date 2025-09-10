#include "Missile.h"

Missile::Missile()
{
    //mp_sprite->m_drawable.set
    sf::Vector2f shape = {10.0f, 10.0f};
    mp_sprite->setShape(shape);
}
