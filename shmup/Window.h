#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Sprite;

class Window
{
public:
    Window();
    virtual ~Window(){}
    
    sf::RenderWindow m_window;

    void clear();
    void display();
    bool isOpen();
    void draw(Sprite& pSprite);
};
