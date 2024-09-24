/*
* This file contain the ball's class which inherit from Item.
* It is with this ball that we will play the game.
*/

#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "GameClock.h"

/**********************************************************
* \brief A simple ball which rebound on a surface
**********************************************************/
class Ball final : public sf::CircleShape
{
public:
    static float const PI; /// the pi value to use. We use two decimal
    /**********************************************************
    * \brief get a random angle between min and max
    *
    * \param min the minimal value
    * \param max the max value
    *
    * \return a float between min and max
    *
    **********************************************************/
    static float getRandomAngle(float min = PI / 12, float max = PI / 6);

    typedef enum
    {
        X,
        Reverse_X,
        Y,
        Reverse_Y
    } Direction;
    typedef enum
    {
        INCREASE_SPEED,
        DECREASE_SPEED,
        NO_EFFECT
    } Effect;
    typedef struct
    {
        Effect effect;
        Direction direction;
    } EffectInfo;
    /**********************************************************
    * \brief Create a ball with a radius that can be played
    *        in a closed area
    *
    **********************************************************/
    explicit Ball(GameClock& game_clock, sf::FloatRect& field);

    /**********************************************************
    * \brief set speed of the ball
    *
    * \param speed => new speed of the ball
    *
    * \return true if the new speed is correct (between 0 and 1)
    *
    **********************************************************/
    bool setSpeed(float speed);

    /**********************************************************
    * \brief get the current speed of the ball
    *
    * \return the speed within the ball move
    *
    **********************************************************/
    float getSpeed() const;

    /**********************************************************
    * \brief get the angle take by the ball with the horizontal
    *
    * \return the angle of trajectory
    *
    **********************************************************/
    float getTrajectoryAngle() const;

    /**********************************************************
    * \brief it moves the ball
    *
    * \return a vector which is the actual position of the ball
    *         after moving
    *
    **********************************************************/
    sf::Vector2f move();

    /**********************************************************
    * \brief change the trajectory of the ball when there are
    *        collision
    *
    * \param new_direction the new direction of the ball
    *
    * \return the actual angle of the trajectory
    *
    **********************************************************/
    float changeTrajectory(Direction new_direction);

    void applyEffect(Effect effect, Direction direction);

    [[nodiscard]] EffectInfo getCurrentEffect() const;

    void addToSpeed(float speed);

private:
    GameClock& m_game_clock; /// it is the clock of a game part. It contains information concerning the different times of game. Should not be destroyed because it is not this class that create it(pointer)
    float m_speed; /// the speed of the ball under 0 and 1. It is in pixels per second
    float m_trajectory_angle; /// the trajectory of the ball. It is the angle describes by the ball and the horizontal
    EffectInfo m_current_effect_info{NO_EFFECT, Y};
};

#endif // BALL_H_INCLUDED
