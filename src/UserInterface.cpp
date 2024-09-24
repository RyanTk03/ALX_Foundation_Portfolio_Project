//
// Implementation of the user interface class.
//
#include <TGUI/Widgets/Panel.hpp>

#include "../inc/UserInterface.h"

#include <TGUI/Widgets/BitmapButton.hpp>
#include <TGUI/Widgets/Grid.hpp>
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/MessageBox.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include "GameParty.h"
#include "theme.h"

UserInterface::UserInterface(tgui::Gui& gui, const sf::Texture& spritesheet, GameData* game_data) :
m_gui(gui), m_game_data(game_data) {
    m_spritesheet.loadFromPixelData(spritesheet.getSize(), spritesheet.copyToImage().getPixelsPtr());
}

bool UserInterface::init()
{
    this->m_current_screen = ScreenEnum::MAIN_MENU;
    this->showMainMenu();
    return true;
}

void UserInterface::showMainMenu()
{
    std::string const point = std::to_string(this->m_game_data->getPoint());
    tgui::Panel::Ptr const main_panel = tgui::Panel::create();
    tgui::Panel::Ptr const top_panel = tgui::Panel::create();
    tgui::Panel::Ptr const body_panel = tgui::Panel::create();
    tgui::HorizontalLayout::Ptr const hlayout = tgui::HorizontalLayout::create();
    tgui::VerticalLayout::Ptr const vlayout = tgui::VerticalLayout::create();
    tgui::BitmapButton::Ptr const point_button = tgui::BitmapButton::create(point);
    tgui::Button::Ptr const play_button = tgui::Button::create("Play");
    tgui::Button::Ptr const quit_button = tgui::Button::create("Quit");
    auto const point_tool_tip = tgui::Label::create("Your total point");
    point_tool_tip->setRenderer(tgui::Theme::getDefault()->getRenderer("ToolTip"));

    main_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    main_panel->setTextSize(28);
    top_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    body_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    main_panel->setAutoLayout(tgui::AutoLayout::Fill);
    top_panel->setHeight("5%");
    top_panel->setAutoLayout(tgui::AutoLayout::Top);
    body_panel->setAutoLayout(tgui::AutoLayout::Fill);
    hlayout->setPosition("parent.innersize - size");
    vlayout->setPosition("(parent.innersize - size) / 2");
    vlayout->setSize(200, 200);
    hlayout->setSize(100, "100%");

    point_button->setToolTip(point_tool_tip);
    hlayout->add(point_button);

    play_button->onClick([&]{ this->showPlayOptions(); });
    vlayout->add(play_button);
    vlayout->addSpace(0.2);
    quit_button->onClick([&]{ this->m_gui.getWindow()->close(); });
    vlayout->add(quit_button);

    top_panel->add(hlayout);
    body_panel->add(vlayout);
    main_panel->add(top_panel);
    main_panel->add(body_panel);
    this->m_gui.removeAllWidgets();
    this->m_gui.add(main_panel);
    this->m_current_screen = ScreenEnum::MAIN_MENU;
}

void UserInterface::showPlayOptions(const std::string& message)
{
    tgui::Panel::Ptr const main_panel = tgui::Panel::create();
    tgui::Panel::Ptr const top_panel = tgui::Panel::create();
    tgui::Panel::Ptr const body_panel = tgui::Panel::create();
    tgui::VerticalLayout::Ptr const vlayout = tgui::VerticalLayout::create();
    tgui::Button::Ptr const play_with_ia_button = tgui::Button::create("You vs IA");
    tgui::Button::Ptr const play_local_button = tgui::Button::create("You vs A friend");
    tgui::Button::Ptr const back_button = tgui::Button::create("Back");
    tgui::MessageBox::Ptr message_box = nullptr;

    main_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    main_panel->setTextSize(28);
    top_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    body_panel->getRenderer()->setBackgroundColor(TGUI_PRIMARY_COLOR);
    main_panel->setAutoLayout(tgui::AutoLayout::Fill);
    top_panel->setHeight("5%");
    top_panel->setAutoLayout(tgui::AutoLayout::Top);
    body_panel->setAutoLayout(tgui::AutoLayout::Fill);
    vlayout->setPosition("(parent.innersize - size) / 2");
    vlayout->setSize(250, 300);

    play_with_ia_button->onClick([&]
    {
        switch (GameParty::play(m_gui, true))
        {
            case 1:
                this->showPlayOptions("You won! +10 points 🎉🎉");
                this->m_game_data->addToPoint(10);
                break;
            case 0:
                this->showPlayOptions("It's a draw!");
                break;
            default:
                this->showPlayOptions("Oops you lose! -10 points, try to take your revenge!");
                this->m_game_data->retrieveToPoint(10);
                break;
        }
    });
    vlayout->add(play_with_ia_button);
    vlayout->addSpace(0.2);
    play_local_button->onClick([&]
    {
        switch (GameParty::play(m_gui, false))
        {
            case 1:
                this->showPlayOptions("You won! +10 points");
                this->m_game_data->addToPoint(10);
                break;
            case 2:
                this->showPlayOptions("Your friend win!");
                break;
            case 0:
                this->showPlayOptions("It's a draw!");
                break;
            default:
                this->showPlayOptions("Oops you lose! -10 points, try to take your revenge!");
                break;
        }
    });
    vlayout->add(play_local_button);
    vlayout->addSpace(0.2);
    back_button->onClick([&]{ this->showMainMenu(); });
    vlayout->add(back_button);

    body_panel->add(vlayout);
    main_panel->add(top_panel);
    main_panel->add(body_panel);
    this->m_gui.removeAllWidgets();
    this->m_gui.add(main_panel);
    if (!message.empty())
    {
        message_box = tgui::MessageBox::create();
        message_box->setText(message);
        message_box->addButton("OK");
        message_box->setHeight(100);
        message_box->setPosition("(parent.innerwidth - width) / 2" ,"parent.top");
        message_box->setAutoLayout(tgui::AutoLayout::Top);
        message_box->onButtonPress([msg_box=message_box.get()]
        {
            msg_box->getParent()->remove(msg_box->shared_from_this());
        });
        m_gui.add(message_box);
    }
    this->m_current_screen = ScreenEnum::PLAY_OPTIONS;
}

void UserInterface::showSettings()
{
    this->m_current_screen = ScreenEnum::SETTINGS;
}

void UserInterface::showShop()
{
    this->m_current_screen = ScreenEnum::SHOP;
}



