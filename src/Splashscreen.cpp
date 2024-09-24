//
// Splashscreen class implementation file.
//
#include "Splashscreen.h"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "theme.h"

Splashscreen::Splashscreen(sf::Texture& texture, std::map<SpritePosition, sf::IntRect> const &map,
                           sf::Vector2u const window_size) : m_texture(texture), m_map(map)
{
    this->m_remap(window_size);
}

void Splashscreen::display(const tgui::Gui& gui_instance, float const duration)
{
    sf::Clock clock;
    float last_time = 0;
    constexpr float FPS = 24.0f;
    sf::Uint8 alpha = 255;
    const auto alpha_increment = static_cast<sf::Uint8>(255 / (FPS * (duration / 2)));
    auto const window = gui_instance.getWindow();
    auto const render_target = gui_instance.getTarget();
    sf::Sprite sprite;
    sf::Event event;

    sprite.setTexture(this->m_texture);
    clock.restart();

    while (window->isOpen() && last_time <= duration)
    {
        window->pollEvent(event);
        if (event.type == sf::Event::Closed)
            window->close();
        else if (event.type == sf::Event::KeyPressed)
            break;
        else if (event.type == sf::Event::Resized)
        {
            this->m_remap(sf::Vector2u(event.size.width, event.size.height));
            this->m_draw(render_target, sprite, alpha);
        }
        else if (clock.getElapsedTime().asSeconds() - last_time >= (1 / FPS))
        {
            if (last_time > duration / 2 && alpha - alpha_increment < 0)
                alpha = 0;
            else
                alpha = alpha + (last_time <= duration / 2 ? - 1 * alpha_increment : alpha_increment);
            last_time = clock.getElapsedTime().asSeconds();
            this->m_draw(render_target, sprite, alpha);
        }
        window->display();
    }
    render_target->clear();
    window->display();
}

void Splashscreen::m_remap(const sf::Vector2u& window_size)
{
    constexpr sf::Uint8 margin = 10;
    this->m_window_size = window_size;
    this->m_position_map[SpritePosition::TOP_LEFT] = sf::Vector2f(margin, margin);

    this->m_position_map[SpritePosition::TOP_RIGHT] = sf::Vector2f(
        static_cast<float>(window_size.x) - static_cast<float>(this->m_map[SpritePosition::TOP_RIGHT].width) - margin,
        margin);

    this->m_position_map[SpritePosition::CENTER] = sf::Vector2f(
        static_cast<float>(window_size.x) / 2 - static_cast<float>(this->m_map[SpritePosition::CENTER].width) / 2,
        static_cast<float>(window_size.y) / 2 - static_cast<float>(this->m_map[SpritePosition::CENTER].height) / 2);

    this->m_position_map[SpritePosition::BOTTOM_LEFT] = sf::Vector2f(
        0 + margin,
        static_cast<float>(window_size.y) - static_cast<float>(this->m_map[SpritePosition::BOTTOM_LEFT].height) - margin);

    this->m_position_map[SpritePosition::BOTTOM_RIGHT] = sf::Vector2f(
        static_cast<float>(window_size.x) - static_cast<float>(this->m_map[SpritePosition::BOTTOM_RIGHT].width) - margin,
        static_cast<float>(window_size.y) - static_cast<float>(this->m_map[SpritePosition::BOTTOM_RIGHT].height) - margin);
}

void Splashscreen::m_draw(sf::RenderTarget* render_target, sf::Sprite& sprite, sf::Uint8 const alpha)
{
    const std::vector<SpritePosition> positions = {
        SpritePosition::TOP_LEFT,
        SpritePosition::TOP_RIGHT,
        SpritePosition::CENTER,
        SpritePosition::BOTTOM_LEFT,
        SpritePosition::BOTTOM_RIGHT
    };
    sf::RectangleShape layer(sf::Vector2f(static_cast<float>(this->m_window_size.x),
        static_cast<float>(this->m_window_size.y)));

    layer.setFillColor(sf::Color(255, 255, 255, alpha));
    render_target->clear(SF_PRIMARY_COLOR);
    for (const auto& pos : positions)
    {
        if (auto it = this->m_map.find(pos); it != this->m_map.end())
        {
            sprite.setTextureRect(this->m_map[pos]);
            sprite.setPosition(this->m_position_map[pos]);
            render_target->draw(sprite);
        }
    }

    render_target->draw(layer);
}
