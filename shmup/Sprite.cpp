#include "Sprite.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameManager.h"

Sprite::Sprite() :
    m_font("retro_font.ttf"),
    m_text(m_font, "")
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

void Sprite::start() {}

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

void Sprite::setText(const std::string& text)
{
    m_text.setCharacterSize(30);
    m_text.setStyle(sf::Text::Bold);
    m_text.setString(text);
    m_text.setOrigin({m_text.getGlobalBounds().size.x * 0.5f, m_text.getGlobalBounds().size.y * 0.5f});
    m_text.setPosition(m_drawable.getPosition());
    m_text.setFillColor({ 255, 255, 255, 255});
}


void Sprite::setRotation(float angle)
{
    m_drawable.setRotation(sf::degrees(angle));
}
