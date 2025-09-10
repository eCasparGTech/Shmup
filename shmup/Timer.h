#pragma once

class Timer
{
public:
    Timer();
    virtual ~Timer(){}
    
    void update();
    unsigned int getDelta();
    float getFps();
    static unsigned int getTime();

private:
    unsigned int m_sysTime;
    unsigned int m_deltaTime;
};
