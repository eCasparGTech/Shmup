#pragma once

#include "Sprite.h"

class GameManager;

// a class without using libraries like sfml or std
class Object
{
public:
    Object();

    virtual ~Object(){}

    sf::Vector2f m_position;
    Sprite* mp_sprite;
    
    // rotation
    //float m_rotation;

    // scale
    //float m_width;
    //float m_height;

    virtual void update();

    void setPosition(sf::Vector2f position);

    // function rotate
    //void rotate(float rotation);

    // function scale
    //void scale(float width, float height);

    void setGameManager(GameManager* manager);
    
protected:
    GameManager* mp_gameManager;
};
