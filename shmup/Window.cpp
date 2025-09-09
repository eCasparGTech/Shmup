#include "Window.h"

void Window::init()
{
    m_window = sf::RenderWindow(sf::VideoMode({ 800, 450 }), "SFML works!");
}

void Window::update()
{
    m_window.clear();

    /*for (auto& s : m_sprites)
    {
        m_window.draw(s);
    }*/
    
    m_window.display();
}

bool Window::isOpen()
{
    return m_window.isOpen();
}

void Window::subscribe(const Sprite sprite)
{
    m_sprites.push_back(sprite);
}
