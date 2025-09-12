#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "framework.h"

class GameManager;

class Sprite
{
public:
    Sprite();
    virtual ~Sprite() {}

    void setWidth(float width);
    void setHeight(float height);
    void setSize(sf::Vector2f shape);
    void setText(const std::string& text);
    sf::Vector2f getSize() const { return m_drawable.getSize(); }
    void setRotation(float angle);

    void setPosition(sf::Vector2f position);
    virtual void start();

    sf::Color baseColor = sf::Color::White;
    void setColor(sf::Color color);

    sf::RectangleShape m_drawable;
    sf::Text m_text;
    sf::Font m_font;

private:
    void updateOrigin();
    GameManager* mp_gameManager;
};
