#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "../inc/GameParty.h"
#include "../inc/Ball.h"
#include "../inc/Paddle.h"
#include "../inc/Collision.h"

sf::Keyboard::Key aiKeySimulation()
{
    auto random_number = rand() % 10000000;

    if (random_number < 1)
    {
        random_number = rand() % 2;
        if (random_number == 0)
            return sf::Keyboard::O;
        return sf::Keyboard::F;
    }
    return sf::Keyboard::Escape;
}

int GameParty::play(tgui::Gui &gui, const bool playing_with_ai)
{
    bool pause = false;
    GameClock game_clock;
    sf::RenderTarget *render_target = gui.getTarget();
    sf::Window *render_window = gui.getWindow();
    auto field_rect = sf::FloatRect(0, 0, static_cast<float>(render_target->getSize().x),
        static_cast<float>(render_target->getSize().y));
    Ball ball(game_clock, field_rect);
    Paddle p1(Paddle::Player::User1, field_rect, game_clock),
    p2(playing_with_ai ? Paddle::Player::IA : Paddle::Player::User2, field_rect, game_clock);
    Collision collision(field_rect, p1, p2, ball);
    sf::Event event;
    bool playing = true;
    int process_result = 0;

    gui.removeAllWidgets();
    game_clock.playTime.start();
    game_clock.last_time_ball_speed_increased = 0;
    while(playing)
    {
        auto [surface, position] = collision.test();
        render_window->pollEvent(event);
        if (game_clock.playTime.getElapsedTime().asSeconds() - game_clock.last_ball_effect_time > 10 &&
            ball.getCurrentEffect().effect != Ball::NO_EFFECT)
        {
            game_clock.last_ball_effect_time = game_clock.playTime.getElapsedTime().asSeconds();
            ball.applyEffect(Ball::NO_EFFECT, Ball::X);
        }
        /*if (game_clock.playTime.getElapsedTime().asSeconds() - game_clock.last_paddle1_effect_time > 10)
        {
            game_clock.last_paddle1_effect_time = game_clock.playTime.getElapsedTime().asSeconds();
        }
        if (game_clock.playTime.getElapsedTime().asSeconds() - game_clock.last_paddle2_effect_time > 10)
        {
            game_clock.last_paddle2_effect_time = game_clock.playTime.getElapsedTime().asSeconds();
        }*/
        if (event.type == sf::Event::Closed)
        {
            playing = false;
            process_result = -2;
            render_window->close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            playing = false;
            process_result = 0;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            pause = !pause;
            if (pause)
                game_clock.playTime.pause();
            else
                game_clock.playTime.start();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I
            && ball.getCurrentEffect().effect == Ball::NO_EFFECT)
        {
            ball.applyEffect(Ball::INCREASE_SPEED, Ball::X);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D
            && ball.getCurrentEffect().effect == Ball::NO_EFFECT)
        {
            ball.applyEffect(Ball::DECREASE_SPEED, Ball::X);
        }
        else if ((playing_with_ai && aiKeySimulation() == sf::Keyboard::O) ||
            (!playing_with_ai && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O &&
                ball.getCurrentEffect().effect == Ball::NO_EFFECT))
        {
            ball.applyEffect(Ball::INCREASE_SPEED, Ball::Reverse_X);
        }
        else if ((playing_with_ai && aiKeySimulation() == sf::Keyboard::F) ||
            (!playing_with_ai && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F &&
                ball.getCurrentEffect().effect == Ball::NO_EFFECT))
        {
            ball.applyEffect(Ball::DECREASE_SPEED, Ball::Reverse_X);
        }
        if (!pause && surface != Collision::Surface::Nothing)
        {
            if(surface == Collision::Surface::LimitLeft ||
                surface == Collision::Surface::LimitRight)
            {
                if(surface == Collision::Surface::LimitLeft)
                    process_result = 2; // Player 2 win
                else
                    process_result = 1; // Player 1 win
                playing = false;
            }
        }

        if (!pause)
        {
            render_target->clear(sf::Color(108, 160, 220));
            render_target->draw(ball);
            render_target->draw(p1);
            render_target->draw(p2);

            p1.move(ball.getPosition(), collision.getLimit());
            p2.move(ball.getPosition(), collision.getLimit());
            ball.move();
            render_window->display();
        }
        if (game_clock.playTime.getElapsedTime().asSeconds() - game_clock.last_time_ball_speed_increased >= 10)
        {
            game_clock.last_time_ball_speed_increased = game_clock.playTime.getElapsedTime().asSeconds();
            ball.addToSpeed(15);
        }
    }
    return process_result;
}
