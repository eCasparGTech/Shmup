#pragma once

#include "Sprite.h"

class GameManager;

// a class without using libraries like sfml or std
class Object
{
public:
    Sprite* mp_sprite;
    
    Object();
    virtual ~Object(){}
    
    // position
    sf::Vector2f m_position;

    // rotation
    float m_rotation;

    // scale
    float m_width;
    float m_height;

    // color
    float m_r, m_g, m_b;

    // function move
    void move(sf::Vector2f distance);

    // function rotate
    //void rotate(float rotation);

    // function scale
    //void scale(float width, float height);
    
    void setGameManager(GameManager* manager);
};
