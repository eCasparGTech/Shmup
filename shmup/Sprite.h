#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "framework.h"

class GameManager;

class Sprite
{
public:    
    Sprite();
    virtual ~Sprite(){}
    
    sf::RectangleShape m_drawable;

    void setPosition(sf::Vector2f position);
    void setShape(sf::Vector2f shape);

private:
    // color
    //float m_r, m_g, m_b;
};
