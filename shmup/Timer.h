#pragma once

class Timer
{
public:
    Timer();
    virtual ~Timer() {}

    void update();
    float getDelta();
    float getFps();
    static float getTime();

private:
    float m_sysTime;
    float m_deltaTime;
};
