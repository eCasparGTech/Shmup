// shmup.cpp : Définit le point d'entrée de l'application.
//
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "framework.h"
#include "shmup.h"
#include <iostream>
#include "Keyboard.h"
#include "Window.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Window win = Window();
    win.init();
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Timer timer;

    Keyboard keyboard;
    
    // Boucle de jeu
    while (win.isOpen())
    {
        /*while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }*/

        timer.update();

        float deltaTime = static_cast<float>(timer.m_deltaTime);

        if (deltaTime == 0.f) continue;
        
        float seconds = deltaTime / 1000.0f;
        float fps = 1 / seconds;
        
        keyboard.update();

        if (keyboard.keyRelease(KeyCode::down))
        {
            // print "a" pressed
            std::cout << "down is pressed" << std::endl;
        }
        
        // render
        win.update();
        
        // window.clear();
        
        // window.draw(shape);
        
        //window.display();
    } 
}
