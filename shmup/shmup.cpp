// shmup.cpp : Définit le point d'entrée de l'application.
#include <SFML/Graphics.hpp>
#include "framework.h"
#include "shmup.h"

#include "GameManager.h"
#include "Window.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Window window;

    GameManager* gameManager = GameManager::getInstance();
    gameManager->setWindow(&window);

    gameManager->start();

    return 0;
}
