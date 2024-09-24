//
// Created by lenovo on 21/09/2024.
//

#ifndef GAMEPARTY_H
#define GAMEPARTY_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>


class GameParty
{
public:
    static int play(tgui::Gui &gui, bool playing_with_ai);
};



#endif //GAMEPARTY_H
