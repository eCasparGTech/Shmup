#include "GameManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Keyboard.h"
#include "Sprite.h"
#include "Timer.h"
#include "Window.h"

GameManager::GameManager()
{
    
}

void GameManager::start()
{
    Timer timer;

    Keyboard keyboard;

    Sprite sprite = Sprite();
    sprite.setGameManager(this);
    
    while (mp_window->isOpen())
    {
        timer.update();

        float deltaTime = static_cast<float>(timer.m_deltaTime);

        if (deltaTime == 0.f) continue;
        
        float seconds = deltaTime * 0.001f;
        float fps = 1 / seconds;
        
        keyboard.update();

        if (keyboard.keyRelease(KeyCode::down))
        {
            // print "a" pressed
            //std::cout << "down is pressed" << std::endl;
        }
        
        // render
        mp_window->clear();
        render();
        mp_window->display();
    }
}


void GameManager::subscribe(Sprite* pSprite)
{
    mp_spriteList.push_back(pSprite);
}

void GameManager::setWindow(Window* pWindow)
{
    mp_window = pWindow;
}

void GameManager::render()
{
    for (Sprite* pSprite : mp_spriteList)
    {
        mp_window->draw(*pSprite);
    }
}
