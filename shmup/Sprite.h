#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
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
    void setRotation(float angle);


    void setPosition(sf::Vector2f position);

    sf::Color baseColor = sf::Color::White;
    void setColor(sf::Color color);

    sf::RectangleShape m_drawable;

private:
    void updateOrigin();
};
