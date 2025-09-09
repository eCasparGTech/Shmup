#include "Sprite.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameManager.h"

Sprite::Sprite()
{
    m_drawable = sf::RectangleShape(sf::Vector2f(100,100));
}

void Sprite::setGameManager(GameManager* manager)
{
    manager->subscribe(this);
}
