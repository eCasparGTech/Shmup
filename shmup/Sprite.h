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

    sf::RectangleShape m_drawable;

    void setPosition(sf::Vector2f position);

    void setColor(sf::Color color);
private:
    // color
    //float m_r, m_g, m_b;
};
