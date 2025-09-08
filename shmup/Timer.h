#pragma once

class Timer
{
public:
    Timer();
    
    DWORD m_deltaTime;
    
    void update();

private:
    DWORD m_sysTime;
};
