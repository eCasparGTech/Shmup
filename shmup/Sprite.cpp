#include "Sprite.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameManager.h"

Sprite::Sprite() :
    m_font("retro_font.ttf"),
    m_text(m_font, ""),
    m_visible(true),
    m_currentColor(sf::Color::White)
{
    m_drawable = sf::RectangleShape();
}

void Sprite::setWidth(float width)
{
    m_drawable.setSize({width, m_drawable.getSize().y});
    updateOrigin();
}

void Sprite::setHeight(float height)
{
    m_drawable.setSize({m_drawable.getSize().x, height});
    updateOrigin();
}

void Sprite::setPosition(sf::Vector2f position)
{
    m_drawable.setPosition(position);
    m_text.setPosition(position);
}

void Sprite::start()
{
    updateOrigin();
}

void Sprite::setColor(sf::Color color)
{
    m_currentColor = color;
    if (m_visible)
    {
        m_drawable.setFillColor(color);
    }
    else
    {
        sf::Color invisibleColor = color;
        invisibleColor.a = 0;
        m_drawable.setFillColor(invisibleColor);
    }
}

void Sprite::updateOrigin()
{
    auto s = m_drawable.getSize();
    m_drawable.setOrigin({s.x * 0.5f, s.y * 0.5f});
}

void Sprite::setSize(sf::Vector2f shape)
{
    m_drawable.setSize(shape);
    updateOrigin();
}

void Sprite::setText(const std::string& text)
{
    m_text.setCharacterSize(30);
    m_text.setStyle(sf::Text::Bold);
    m_text.setString(text);
    m_text.setOrigin({m_text.getGlobalBounds().size.x * 0.5f, m_text.getGlobalBounds().size.y * 0.5f});
    m_text.setPosition(m_drawable.getPosition());
    m_text.setFillColor({255, 255, 255, 255});
}

void Sprite::setRotation(float angle)
{
    m_drawable.setRotation(sf::degrees(angle));
}

void Sprite::setVisible(bool visible)
{
    if (m_visible == visible) return;

    m_visible = visible;

    if (visible)
    {
        m_drawable.setFillColor(m_currentColor);
    }
    else
    {
        sf::Color invisibleColor = m_currentColor;
        invisibleColor.a = 0;
        m_drawable.setFillColor(invisibleColor);
    }
}
