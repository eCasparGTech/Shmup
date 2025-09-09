#include "framework.h"
#include "Timer.h"

Timer::Timer()
{
    m_sysTime = timeGetTime();
    m_deltaTime = 0.0f;
}

void Timer::update()
{
    m_deltaTime = timeGetTime() - m_sysTime;
    m_sysTime = timeGetTime();
}

float Timer::getDelta()
{
    return static_cast<float>(m_deltaTime);
}

float Timer::getFps()
{
    float seconds = getDelta() * 0.001f;
    return (seconds != 0) ? 1 / seconds : 0.0f;
}
