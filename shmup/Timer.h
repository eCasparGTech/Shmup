#pragma once

class Timer
{
public:
    Timer();
    virtual ~Timer(){}
    
    unsigned int m_deltaTime;
    
    void update();

private:
    unsigned int m_sysTime;
};
