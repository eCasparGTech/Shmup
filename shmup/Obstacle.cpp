#include "Obstacle.h"

Obstacle::Obstacle() : Object()
{
    
}

void Obstacle::start()
{
    Object::start();
    setType(ObjectType::TObstacle);
    mp_sprite->baseColor = {255, 150, 0, 255};
    mp_sprite->setColor(mp_sprite->baseColor);
    setPosition({100.0f, 100.0f});
    setSize({50.0f, 100.0f});
}