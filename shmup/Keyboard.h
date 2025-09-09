#pragma once

enum KeyCode
{
    w = 87,
    a = 65,
    s = 83,
    d = 68,
    e = 69,
    space = 32,
    enter = 13,
    escape = 27,
    left = 37,
    right = 39,
    up = 38,
    down = 40
};

class Keyboard
{
private:
    typedef unsigned char byte;
    static constexpr int KEYBOARD_SIZE = 256;
    static byte m_keyboardState[KEYBOARD_SIZE];
    
public:
    Keyboard();
    virtual ~Keyboard(){}
    
    void update();

    bool keyDown(int key);
    bool keyUp(int key);
    bool keyPress(int key);
    bool keyRelease(int key);
};
