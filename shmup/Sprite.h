#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

class GameManager;

class Sprite
{
public:
    sf::RectangleShape m_drawable;
    
    Sprite();
    virtual ~Sprite(){}

    void setGameManager(GameManager* manager);
};
