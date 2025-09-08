#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Sprite.h"

class Window
{
    std::vector<Sprite> m_sprites;
public:
    sf::RenderWindow m_window;

    void init();
    void update();
    bool isOpen();
    void subscribe(const Sprite& sprite);
};