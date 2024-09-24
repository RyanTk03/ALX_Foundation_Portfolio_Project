#include <ctime>
#include <cstdlib>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "GameData.h"
#include "Splashscreen.h"
#include "spritesheet_map.h"
#include "UserInterface.h"

int main()
{
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    GameData *game_data = GameData::load();
    tgui::Theme::setDefault("../assets/themes/Black.txt");
    auto WINDOW_SIZE = sf::Vector2u(980, 600);
    sf::RenderWindow window({WINDOW_SIZE.x, WINDOW_SIZE.y}, "Crazy Pong");
    sf::Texture spritesheet;
    tgui::Gui gui(window);
    Splashscreen splashscreen(spritesheet, {
                                  {Splashscreen::SpritePosition::BOTTOM_LEFT, sf::IntRect(ATTRIBUTION_1_MAP)},
                                  {Splashscreen::SpritePosition::BOTTOM_RIGHT, sf::IntRect(ATTRIBUTION_2_MAP)},
                                  {Splashscreen::SpritePosition::CENTER, sf::IntRect(LOGO_MAP)}},
                              WINDOW_SIZE);

    if (sf::Image icon; icon.loadFromFile("../assets/icon.png"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    if (!spritesheet.loadFromFile("../assets/spritesheet.png"))
        return -1;

    splashscreen.display(gui, 5);

    UserInterface ui(gui, spritesheet, game_data);
    if (ui.init())
        gui.mainLoop();
}
