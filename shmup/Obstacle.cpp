#include "Obstacle.h"

Obstacle::Obstacle() : Object()
{
    
}

void Obstacle::start()
{
    Object::start();
    setType(ObjectType::TObstacle);
    mp_sprite->setColor({255, 150, 0, 255});
    setPosition({100.0f, 100.0f});
    setSize({50.0f, 100.0f});
}