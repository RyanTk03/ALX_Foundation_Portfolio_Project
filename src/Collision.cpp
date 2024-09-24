#include <SFML/Graphics.hpp>

#include "../inc/Collision.h"

Collision::Collision(const sf::FloatRect& limit, const Paddle& paddle1, const Paddle& paddle2, Ball& ball) :
m_paddle1(paddle1), m_paddle2(paddle2), m_ball(ball), m_limit(limit)
{
    m_info.surface = Surface::Nothing;
    m_info.position = m_ball.getPosition();
}

Collision::Information Collision::test()
{
    const sf::FloatRect ball(m_ball.getPosition(), sf::Vector2f(m_ball.getRadius() * 2, m_ball.getRadius() * 2));
    const sf::FloatRect paddle1(m_paddle1.getPosition(), m_paddle1.getSize());
    const sf::FloatRect paddle2(m_paddle2.getPosition(), m_paddle2.getSize());

    m_info.surface = Surface::Nothing;
    m_info.position = sf::Vector2f(ball.left, ball.top);

    // Collision test with the right limit
    if (ball.left + ball.width >= m_limit.left + m_limit.width)
    {
        m_info.surface = Surface::LimitRight;
    }
    // Collision test with the left limit
    else if (ball.left <= m_limit.left)
    {
        m_info.surface = Surface::LimitLeft;
    }
    // Collision test with the top limit
    else if (ball.top <= m_limit.top)
    {
        m_info.surface = Surface::LimitTop;
        m_ball.changeTrajectory(Ball::Direction::Y);
        if (ball.top < m_limit.top)
            m_ball.setPosition(ball.left, m_limit.top);
    }
    // Collision test with the bottom limit
    else if (ball.top + ball.height >= m_limit.top + m_limit.height)
    {
        m_info.surface = Surface::LimitBottom;
        m_ball.changeTrajectory(Ball::Direction::Reverse_Y);
        if (ball.top + ball.height > m_limit.top + m_limit.height)
            m_ball.setPosition(ball.left, m_limit.top + m_limit.height - ball.height);
    }
    // Collision test with the left paddle
    else if ((ball.left <= (paddle1.left + paddle1.width)) && (ball.top + ball.height > paddle1.top) &&
        (ball.top <= (paddle1.top + paddle1.height)))
    {
        m_info.surface = Surface::PaddleLeft;
        m_ball.changeTrajectory(Ball::Direction::X);
        if (ball.left < paddle1.left + paddle1.width)
            m_ball.setPosition(paddle1.left + paddle1.width, ball.top);

    }
    // Collision test with the right paddle
    else if ((ball.left + ball.width >= paddle2.left) && (ball.top + ball.height > paddle2.top) &&
        (ball.top <= paddle2.top + paddle2.height))
    {
        m_info.surface = Surface::PaddleRight;
        m_ball.changeTrajectory(Ball::Direction::Reverse_X);
        if (ball.left + ball.width > paddle2.left)
            m_ball.setPosition(paddle2.left - ball.width, ball.top);
    }

    return m_info;;
}

bool Collision::setLimit(const sf::FloatRect& limit)
{
    if(limit == sf::FloatRect())
        return false;
    m_limit = limit;
    return true;
}

const sf::FloatRect& Collision::getLimit() const
{
    return m_limit;
}
