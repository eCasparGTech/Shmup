#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class GameManager;

class Sprite
{
public:
    sf::RectangleShape m_drawable;
    
    Sprite();
    virtual ~Sprite(){}

    void setPosition(sf::Vector2f position);

private:
    // color
    //float m_r, m_g, m_b;
};
