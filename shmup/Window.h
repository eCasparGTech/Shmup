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
    void draw(sf::Drawable& drawable);
    void setTitle(std::string title);
    sf::Vector2u getDimensions();

    sf::RenderWindow m_window;
};