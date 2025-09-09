#pragma once

#include "Sprite.h"

class GameManager;

// a class without using libraries like sfml or std
class Object
{
public:    
    Object();
    virtual ~Object(){}
    
    Sprite* mp_sprite;

    void handleInput();
    void update();

    // function move
    void move(sf::Vector2f distance);

    // function rotate
    //void rotate(float rotation);

    // function scale
    //void scale(float width, float height);
    
    void setGameManager(GameManager* manager);
private:
    // position
    sf::Vector2f m_position;
    GameManager* mp_gameManager;

    // rotation
    //float m_rotation;

    // scale
    //float m_width;
    //float m_height;

    // color
    //float m_r, m_g, m_b;
};
