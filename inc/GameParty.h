#ifndef GAMEPARTY_H
#define GAMEPARTY_H

#include <TGUI/Backend/SFML-Graphics.hpp>


class GameParty
{
public:
    static int play(tgui::Gui &gui, bool playing_with_ai);
};



#endif //GAMEPARTY_H
