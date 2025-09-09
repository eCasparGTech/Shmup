#pragma once

class Timer
{
public:
    Timer();
    virtual ~Timer(){}
    
    void update();
    float getDelta();
    float getFps();
private:
    unsigned int m_sysTime;
    unsigned int m_deltaTime;
};
