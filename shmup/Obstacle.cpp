#include "Obstacle.h"
#include "GameManager.h"
#include "Window.h"

Obstacle::Obstacle() : Object() {}

void Obstacle::start()
{
    Object::start();
    setType(ObjectType::TObstacle);
    mp_sprite->baseColor = {127, 127, 127, 255};
    mp_sprite->setColor(mp_sprite->baseColor);

    float randomW = std::rand() % 45;
    float randomH = std::rand() % 80;
    setSize({randomW, randomH});

    sf::Vector2u dimensionsInt = mp_gameManager->getWindow()->getDimensions();
    sf::Vector2f dimensions = {static_cast<float>(dimensionsInt.x), static_cast<float>(dimensionsInt.y)};

    float randomX = ((std::rand() % 801) + 100) * 0.001f;
    float randomY = ((std::rand() % 801) + 100) * 0.001f;

    setPosition({dimensions.x * randomX - getSize().x * 0.5f, dimensions.y * randomY - getSize().y * 0.5f});
}
