#include "framework.h"
#include "Timer.h"

Timer::Timer()
{
    m_sysTime = getTime();
    m_deltaTime = 0.0f;
}

void Timer::update()
{
    unsigned int time = getTime();
    m_deltaTime = time - m_sysTime;
    m_sysTime = time;
}

unsigned int Timer::getDelta()
{
    return m_deltaTime;
}

float Timer::getFps()
{
    float seconds = static_cast<float>(getDelta()) * 0.001f;
    return (static_cast<int>(seconds) != 0) ? 1 / seconds : 0.0f;
}

unsigned int Timer::getTime()
{
    return static_cast<unsigned int>(timeGetTime());
}
