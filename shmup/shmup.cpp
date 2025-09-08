// shmup.cpp : Définit le point d'entrée de l'application.
//
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "framework.h"
#include "shmup.h"

#include <iostream>

#include "Keyboard.h"
#include "Window.h"

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code:
/*
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

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
         
        //window.draw()
        //window.display();
    } 
}

//
//  FONCTION: MyRegisterClass()
//
//  OBJECTIF: Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    //wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHMUP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SHMUP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION: InitInstance(HINSTANCE, int)
//
//   OBJECTIF: enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES:
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
