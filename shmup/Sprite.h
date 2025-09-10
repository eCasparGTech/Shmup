#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class GameManager;

class Sprite
{
public:    
    Sprite();
    virtual ~Sprite(){}
    
    sf::RectangleShape m_drawable;

    void setPosition(sf::Vector2f position);

private:
    // color
    //float m_r, m_g, m_b;
};
