#include "framework.h"
#include "Timer.h"

Timer::Timer()
{
    m_sysTime = getTime();
    m_sysTimeMs = getTimeMs();
    m_deltaTime = 0.0f;
    m_deltaTimeMs = 0;
}

void Timer::update()
{
    float time = getTime();
    unsigned int timeMs = getTimeMs();
    m_deltaTime = time - m_sysTime;
    m_deltaTimeMs = timeMs - m_sysTimeMs;
    m_sysTime = time;
    m_sysTimeMs = timeMs;
}

float Timer::getDelta()
{
    return m_deltaTime;
}

unsigned int Timer::getDeltaMs()
{
    return m_deltaTimeMs;
}

float Timer::getFps()
{
    float seconds = getDeltaMs() * 0.001f;
    return seconds != 0.0f ? 1.0f / seconds : 0.0f;
}

float Timer::getTime()
{
    return static_cast<float>(timeGetTime()) * 0.001f;
}

unsigned int Timer::getTimeMs()
{
    return timeGetTime();
}
