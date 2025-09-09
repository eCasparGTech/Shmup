#include "Window.h"

#include "Sprite.h"

Window::Window()
{
    m_window = sf::RenderWindow(sf::VideoMode({ 800, 450 }), "SFML works!");
}

void Window::clear()
{
    m_window.clear();
}

void Window::display()
{
    m_window.display();
}

bool Window::isOpen()
{
    return m_window.isOpen();
}

void Window::draw(Sprite& pSprite)
{
    m_window.draw(pSprite.m_drawable);
}
