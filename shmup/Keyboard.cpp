#include "framework.h"
#include "Keyboard.h"

Keyboard::byte Keyboard::m_keyboardState[Keyboard::KEYBOARD_SIZE] = {0}; // Définition

Keyboard::Keyboard()
{
    
}

void Keyboard::update()
{
    for (int i = 0; i < KEYBOARD_SIZE; i++)
    {
        if (GetAsyncKeyState(i) & 0x8000)
        {
            if (m_keyboardState[i] == 0)
                m_keyboardState[i] = 1;
            else
                m_keyboardState[i] = 2;
        }
        else
        {
            if (m_keyboardState[i] == 2)
                m_keyboardState[i] = 3;
            else
                m_keyboardState[i] = 0;
        }
    }
}

bool Keyboard::keyDown(int key) { return m_keyboardState[key] == 2; }
bool Keyboard::keyUp(int key) { return m_keyboardState[key] == 0; }
bool Keyboard::keyPress(int key) { return m_keyboardState[key] == 1; }
bool Keyboard::keyRelease(int key) { return m_keyboardState[key] == 3; }
