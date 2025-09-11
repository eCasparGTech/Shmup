#include "Sprite.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

Sprite::Sprite()
{
    m_drawable = sf::RectangleShape();
    updateOrigin();
}

void Sprite::setWidth(float width)
{
    m_drawable.setSize({width, m_drawable.getSize().y});
}

void Sprite::setHeight(float height)
{
    m_drawable.setSize({m_drawable.getSize().x, height});
}

void Sprite::setPosition(sf::Vector2f position)
{
    m_drawable.setPosition(position);
}

void Sprite::setColor(sf::Color color)
{
    m_drawable.setFillColor(color);
}

void Sprite::updateOrigin()
{
    auto s = m_drawable.getSize();
    m_drawable.setOrigin({s.x * 0.5f, s.y * 0.5f});
}

void Sprite::setSize(sf::Vector2f shape)
{
    m_drawable.setSize(shape);
}
