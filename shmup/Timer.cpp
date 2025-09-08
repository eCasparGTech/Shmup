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