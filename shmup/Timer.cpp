#include "framework.h"
#include "Timer.h"

Timer::Timer()
{
    m_sysTime = getTime();
    m_deltaTime = 0.0f;
}

void Timer::update()
{
    float time = getTime();
    m_deltaTime = time - m_sysTime;
    m_sysTime = time;
}

float Timer::getDelta()
{
    return m_deltaTime;
}

float Timer::getFps()
{
    float seconds = getDelta() * 0.001f;
    return (static_cast<int>(seconds) != 0) ? 1 / seconds : 0.0f;
}

float Timer::getTime()
{
    return static_cast<float>(timeGetTime()) * 0.001f;
}
