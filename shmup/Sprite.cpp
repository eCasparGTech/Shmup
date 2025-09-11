#include "Sprite.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

Sprite::Sprite()
{
    m_drawable = sf::RectangleShape();
}

void Sprite::setWidth(float width)
{
    m_drawable.setSize({ width, m_drawable.getSize().y });
}

void Sprite::setHeight(float height)
{
    m_drawable.setSize({ m_drawable.getSize().x, height });
}

void Sprite::setPosition(sf::Vector2f position)
{
    sf::Vector2f centeredPosition = { position.x - m_drawable.getSize().x * 0.5f, position.y - m_drawable.getSize().y * 0.5f };
    m_drawable.setPosition(centeredPosition);
}

void Sprite::setColor(sf::Color color)
{
    m_drawable.setFillColor(color);
}

void Sprite::setSize(sf::Vector2f shape)
{
    m_drawable.setSize(shape);
}
