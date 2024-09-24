//
// Definition of the user interface class.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <TGUI/Backend/SFML-Graphics.hpp>

#include "GameData.h"


class UserInterface
{
public:
    enum class ScreenEnum
    {
        MAIN_MENU,
        SETTINGS,
        SHOP,
        PLAY_OPTIONS,
    };
    explicit UserInterface(tgui::Gui& gui, const sf::Texture& spritesheet, GameData* game_data);
    bool init();
    void showMainMenu();
    void showSettings();
    void showShop();
    void showPlayOptions(const std::string& message = "");

private:
    ScreenEnum m_current_screen{ScreenEnum::MAIN_MENU};
    tgui::Gui& m_gui;
    tgui::Texture m_spritesheet;
    GameData* m_game_data;
};



#endif //USERINTERFACE_H
