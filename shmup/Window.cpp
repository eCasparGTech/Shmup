#include "Window.h"
#include "Sprite.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

Window::Window()
{
    m_window = sf::RenderWindow(sf::VideoMode({ 450, 800 }), "SFML works!");
}

void Window::pollEvents()
{
    while (auto event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
    }
}

void Window::clear()
{
    m_window.clear();
}

void Window::display()
{
    m_window.display();
}

bool Window::isOpen() const
{
    return m_window.isOpen();
}

void Window::draw(Sprite& pSprite)
{
    m_window.draw(pSprite.m_drawable);
}