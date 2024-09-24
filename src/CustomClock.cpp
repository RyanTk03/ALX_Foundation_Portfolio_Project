#include "../inc/CustomClock.h"

CustomClock::CustomClock() : m_state(Paused)
{}

void CustomClock::start()
{
    if(m_state != Started)
    {
        m_clock.restart();
        m_state = Started;
    }
}

void CustomClock::pause()
{
    if(m_state != Paused)
    {
        m_state = Paused;
        m_elapsed_time += m_clock.getElapsedTime();
    }
}

void CustomClock::reinitialize()
{
    m_clock.restart();
    pause();
    m_elapsed_time = sf::Time::Zero;
}

sf::Time CustomClock::getElapsedTime() const
{
    sf::Time time;

    if (m_state == Paused)
    {
        time = m_elapsed_time;
    }
    else
    {
        time = m_clock.getElapsedTime() + m_elapsed_time;
    }

    return time;
}