#pragma once

// a class without using libraries like sfml or std
class Object
{
public:
    // position
    float m_x;
    float m_y;

    // rotation
    float m_rotation;

    // scale
    float m_width;
    float m_height;

    // color
    float m_r, m_g, m_b;

    // function move
    void move(float x, float y);

    // function rotate
    void rotate(float rotation);

    // function scale
    void scale(float width, float height);

    // function draw
    void draw();
};
