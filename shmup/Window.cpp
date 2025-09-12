#include "Window.h"
#include "Sprite.h"
#include <SFML/Window/Event.hpp>

Window::Window()
{
    m_window = sf::RenderWindow(sf::VideoMode({ 584, 876 }), "SFML works!", sf::Style::None);
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
    if (pSprite.m_text.getString() != "")
        m_window.draw(pSprite.m_text);
}

void Window::draw(sf::Drawable& drawable)
{
    m_window.draw(drawable);
}

void Window::setTitle(std::string title)
{
    m_window.setTitle(title);
}

sf::Vector2u Window::getDimensions()
{
    return m_window.getSize();
}
