#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main()
{
    sf::RenderWindow window{{800, 600}, "TGUI example - SFML_GRAPHICS backend"};
    tgui::Gui gui{window};
    const tgui::Button::Ptr button = tgui::Button::create("Test Button");
    const auto editBox = tgui::EditBox::create();

    gui.add(editBox, "MyWidgetName");
    gui.add(button);

    gui.mainLoop(); // See below for how to use your own main loop
}
