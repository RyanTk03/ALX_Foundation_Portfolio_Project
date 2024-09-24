#ifndef PADDLE_H
#define PADDLE_H
#include <SFML/Graphics.hpp>

#include "GameClock.h"


class Paddle final : public sf::RectangleShape {
public:
    typedef enum
    {
        Top, Bottom
    } Direction;

    typedef enum
    {
        IA, User1, User2
    } Player;

    typedef enum
    {
        PADDLE_HEIGHT_INCREASE,
        PADDLE_HEIGHT_DECREASE,
    } PaddleEffect;

    typedef struct
    {
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
    } KeyMap;

    /**********************************************************
    * \brief Construct a simple paddle
    *
    * \param player the player that use the paddle
    * \param field
    * \param game_clock
    *
    **********************************************************/
    explicit Paddle(Player player, const sf::FloatRect& field, GameClock& game_clock);

    /**********************************************************
    * \brief move the paddle
    *
    * \param ballPosition the position of the ball to know
    *   if the paddle should be moved
    * \param field_rect the field where the paddle can move
    *
    **********************************************************/
    void move(const sf::Vector2f& ballPosition, const sf::FloatRect& field_rect);

    /**********************************************************
    * \brief get the speed of the paddles
    *
    * \return the speed of the paddles
    *
    **********************************************************/
    float getSpeed() const;

    /**********************************************************
    * \brief set the power of the paddles
    *
    * \param speed the new speed of the paddles
    *
    **********************************************************/
    void setSpeed(float speed);

private:
    bool m_can_move_up; ///< If the paddle can move up
    bool m_can_move_down; ///< If the paddle can move down
    float m_speed; ///< The speed of the paddles: in pixels per second
    Player m_player; ///< The player (the IA or a physical user)
    KeyMap m_key_map; ///< A map which contains the command of the game
    GameClock& m_game_clock; ///< Represent the game time manager
};



#endif //PADDLE_H
