#include "SFML/Graphics.hpp"

#include "../inc/Paddle.h"

#include <iostream>

Paddle::Paddle(const Player player, const sf::FloatRect& field, GameClock& game_clock) :
sf::RectangleShape(sf::Vector2f(30, 100)), m_can_move_up(true), m_can_move_down(true),
m_speed(10), m_player(player), m_key_map(), m_game_clock(game_clock)
{
    setOutlineThickness(-2);
    setOutlineColor(sf::Color::White);
    setFillColor(sf::Color::Green);
    float x = 2;
    if (player != User1)
        x = field.left + field.width - getSize().x - 2;

    setPosition(sf::Vector2f(x, field.top + (field.height / 2) - (getSize().y / 2)));

    if (player == User1)
    {
        m_key_map.up = sf::Keyboard::Up;
        m_key_map.down = sf::Keyboard::Down;
    }
    else if (player == User2)
    {
        m_key_map.up = sf::Keyboard::Q;
        m_key_map.down = sf::Keyboard::A;
    }
}

void Paddle::move(const sf::Vector2f& ballPosition, const sf::FloatRect& field_rect)
{
    constexpr float elapsed_time = 1;

    if(m_can_move_down)
    {
        if((m_player == IA && ballPosition.y > (getPosition().y + getSize().y)) ||
            sf::Keyboard::isKeyPressed(m_key_map.down))
        {
            RectangleShape::move(0, (m_speed * elapsed_time));
            if (m_can_move_up == false)
                m_can_move_up = true;
            if (getPosition().y + getSize().y >= field_rect.top + field_rect.height)
                m_can_move_down = false;
        }
    }
    if(m_can_move_up)
    {
        if((m_player == IA && ballPosition.y < getPosition().y) || sf::Keyboard::isKeyPressed(m_key_map.up))
        {
            RectangleShape::move(0, -(m_speed * elapsed_time));
            if (m_can_move_down == false)
                m_can_move_down = true;
            if (getPosition().y <= field_rect.top)
                m_can_move_up = false;
        }
    }
}

float Paddle::getSpeed() const
{
    return m_speed;
}

void Paddle::setSpeed(float const speed)
{
    m_speed = speed;
}
