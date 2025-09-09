#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "Sprite.h"

class Sprite;

class Window
{
public:
    sf::RenderWindow m_window;
    std::vector<Sprite> m_sprites;

    void init();
    void update();
    bool isOpen();
    void subscribe(const Sprite sprite);
};
