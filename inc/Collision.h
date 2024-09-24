/*
* This file contain the collision class.
* An object instanced with this class manage the collision between the screen objects.
* In our case, it manages the collision between the ball? the paddles and play area limits
*/

#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "Ball.h"
#include "Paddle.h"

/*
    This is the collision class
*/
class Collision
{
public:
    typedef enum
    {
        PaddleLeft, PaddleRight, LimitLeft, LimitRight, LimitTop, LimitBottom, Nothing
    } Surface;


    /**********************************************************
    * \brief This structure contains the information relative
    *        to the collision. It will update each time there
    *        is collision.
    *
    **********************************************************/
    typedef struct
    {
        Surface surface = Nothing;
        sf::Vector2f position; ///Contain the surface with which the ball collided
    } Information;


    /**********************************************************
    * \brief It creates a collision manager with the paddles
    *        and the ball to manage
    *
    * \param limit the limit of game
    * \param paddle1 the right paddle
    * \param paddle2 the left paddle
    * \param ball the ball which is moved
    *
    **********************************************************/
    Collision(const sf::FloatRect& limit, const Paddle& paddle1, const Paddle& paddle2, Ball& ball);

    /**********************************************************
    * \brief It manages the collision between the ball and the
    *        paddles
    *
    * \return true if there is collision and false else
    *
    **********************************************************/
    Information test();


    /**********************************************************
    * \brief set the zone where we want to manage collision
    *
    * \param limit the new zone where we manage the collision
    *
    * \return true unless the rectangle have an unavailable
    *         position or unavailable size like (-1, 0, 0, -2)
    *
    **********************************************************/
    bool setLimit(const sf::FloatRect& limit);


    /**********************************************************
    * \brief get the zone where the ball is played
    *
    * \return the rectangle area where the ball can move
    *
    **********************************************************/
    [[nodiscard]] const sf::FloatRect& getLimit() const;

private:
    const Paddle& m_paddle1;
    const Paddle& m_paddle2;
    Ball& m_ball;
    Information m_info; ///< contain the collision information when there is collision
    sf::FloatRect m_limit; ///< this rectangle is the area where the collision will be manage
};

#endif // COLLISION_H_INCLUDED

