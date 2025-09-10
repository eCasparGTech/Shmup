#pragma once

#include "Sprite.h"

class GameManager;

class Object
{
public:
    Object();
    virtual ~Object() { delete mp_sprite; }

    sf::Vector2f m_position;
    Sprite* mp_sprite;

    // rotation
    //float m_rotation;

    // scale
    float getWidth() { return mp_width; }
    float getHeight() { return mp_height; }
    void setWidth(float width);
    void setHeight(float height);

    void setSize(sf::Vector2f size);

    virtual void update();

    void setPosition(sf::Vector2f position);

    // function rotate
    //void rotate(float rotation);

    // function scale
    //void scale(float width, float height);

    static float getDistance(Object* objectA, Object* objectB);
    static float getDistance(sf::Vector2f* aPosition, sf::Vector2f* bPosition);

protected:
    GameManager* mp_gameManager = nullptr;

private:
    float mp_width;
    float mp_height;
};
