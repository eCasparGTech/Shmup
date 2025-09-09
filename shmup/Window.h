#pragma once
#include <SFML/Graphics.hpp>

class Sprite;

class Window
{
public:
    Window();
    virtual ~Window(){}

    void pollEvents();
    void clear();
    void display();
    bool isOpen() const;
    void draw(Sprite& pSprite);

    sf::RenderWindow m_window;
};