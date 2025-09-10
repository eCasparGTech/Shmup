#include "Sprite.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

Sprite::Sprite()
{
    m_drawable = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
}

void Sprite::setPosition(sf::Vector2f position)
{
    sf::Vector2f centeredPosition = { position.x - m_drawable.getSize().x * 0.5f, position.y - m_drawable.getSize().y * 0.5f };
    m_drawable.setPosition(centeredPosition);
}

void Sprite::setShape(sf::Vector2f shape)
{
    m_drawable.setSize(shape);
}
