/*
This file contain a structure will permit us to
    control the time during a game part.
*/
#ifndef GAMECLOCK_H_INCLUDED
#define GAMECLOCK_H_INCLUDED

#include "CustomClock.h"

///< This struct will be used to manage the time in one game part
typedef struct
{
    CustomClock playTime; ///< The clock of the game
    float last_ball_effect_time = 0.f; ///< The last time an effect was applied to the ball
    float last_paddle1_effect_time = 0.f; ///< The last time an effect was applied to the paddle1
    float last_paddle2_effect_time = 0.f; ///< The last time an effect was applied to the paddle2
    float last_ball_move_time = 0.f; ///< The last time the ball move in one game part
    float last_time_ball_speed_increased = 0.f; ///< The last time the ball speed was increased
} GameClock;

#endif // GAMECLOCK_H_INCLUDED
