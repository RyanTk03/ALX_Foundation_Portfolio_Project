#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "../inc/Ball.h"
#include "../inc/Collision.h"

const float Ball::PI = 3.14;

Ball::Ball(GameClock& game_clock, sf::FloatRect& field): sf::CircleShape(13),  m_game_clock(game_clock),
m_speed(450)
{
    setPosition(field.left + (field.width / 2) - getRadius(), field.top + (field.height / 2) - getRadius());
    m_trajectory_angle = getRandomAngle();
    if (rand() % 2 == 0)
        m_trajectory_angle *= -1;
    this->setFillColor(sf::Color(88, 127, 209));
    this->setOutlineThickness(-2);
}

bool Ball::setSpeed(const float speed)
{
    if(speed <= 0 && speed > 1)
        return false;
    m_speed = speed;
    return true;
}

float Ball::getSpeed() const
{
    return m_speed;
}

sf::Vector2f Ball::move()
{
    const auto elapsedTime = m_game_clock.playTime.getElapsedTime().asSeconds() - m_game_clock.last_ball_move_time;
    sf::Vector2f ballDirection; // the x and y to displace
    float speed = m_speed;

    if ((m_current_effect_info.effect == INCREASE_SPEED && m_current_effect_info.direction == X
        && std::sin(m_trajectory_angle) > 0) || (m_current_effect_info.effect == INCREASE_SPEED  &&
            m_current_effect_info.direction == Reverse_X && std::sin(m_trajectory_angle) < 0))
    {
        speed *= 2;
    }
    if ((m_current_effect_info.effect == DECREASE_SPEED && m_current_effect_info.direction == X
        && std::sin(m_trajectory_angle) > 0) || (m_current_effect_info.effect == DECREASE_SPEED  &&
            m_current_effect_info.direction == Reverse_X && std::sin(m_trajectory_angle) < 0))
    {
        speed /= 2;
    }

    ballDirection.x = std::cos(m_trajectory_angle) * speed * static_cast<float>(elapsedTime);
    ballDirection.y = std::sin(m_trajectory_angle) * speed * static_cast<float>(elapsedTime);

    CircleShape::move(ballDirection.x, ballDirection.y); // move the ball
    m_game_clock.last_ball_move_time = m_game_clock.playTime.getElapsedTime().asSeconds();

    return getPosition();
}

float Ball::changeTrajectory(const Direction new_direction)
{
    if(new_direction == Reverse_X)
    {
        m_trajectory_angle = getRandomAngle(11 * (PI / 12), 5 * (PI / 6));
        if (rand() % 2 == 0)
            m_trajectory_angle *= -1;
    }
    else if (new_direction == X)
    {
        m_trajectory_angle = getRandomAngle();
        if (rand() % 2 == 0)
            m_trajectory_angle *= -1;
    }
    else if(new_direction == Y || new_direction == Reverse_Y)
        m_trajectory_angle *= -1;

    return m_trajectory_angle;
}

float Ball::getTrajectoryAngle() const
{
    return m_trajectory_angle;
}

float Ball::getRandomAngle(const float min, const float max) {
    const float random_fraction = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    return min + random_fraction * (max - min);
}

void Ball::applyEffect(Effect const effect, Direction const direction)
{
    m_current_effect_info.direction = direction;
    m_current_effect_info.effect = effect;
}

Ball::EffectInfo Ball::getCurrentEffect() const
{
    return m_current_effect_info;
}

void Ball::addToSpeed(const float speed)
{
    m_speed += speed;
}
