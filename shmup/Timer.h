#pragma once

class Timer
{
public:
    Timer();
    virtual ~Timer() {}

    void update();
    float getDelta();
    unsigned int getDeltaMs();
    float getFps();
    static float getTime();
    unsigned int getTimeMs();

private:
    float m_sysTime;
    float m_deltaTime;
    unsigned int m_sysTimeMs;
    unsigned int m_deltaTimeMs;
};
