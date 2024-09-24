//
// Splashscreen class definition file.
//
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

/**
 * SplashScreen class
 *
 * This class is used to create a splash screen using a sprite stored as a texture
 * and the coordinates of the part of the sprite to use as the splash screen.
 */
class Splashscreen
{
public:
    // Definition of an enumerated type 'Position' to represent possible locations
    enum class SpritePosition
    {
        TOP_LEFT,    // Top left corner
        TOP_RIGHT,   // Top right corner
        BOTTOM_LEFT, // Bottom left corner
        BOTTOM_RIGHT,// Bottom right corner
        CENTER       // Center
    };

    /**
     * Constructor
     *
     * @param texture The TGUI texture object containing the sprite
     * @param map The TGUI IntRect object defining the coordinates of the part of the sprite to use as the splash screen
     * @param window_size The TGUI Vector2u object containing the size of the window
     */
    Splashscreen(sf::Texture& texture, std::map<SpritePosition, sf::IntRect> const &map, sf::Vector2u window_size);

    /**
     * Display the splash screen with a fade-in and fade-out effect
     *
     * This method creates a sprite from the texture and coordinates, positions it in the center of the window,
     * and displays it with a fade-in and fade-out effect.
     *
     * @param gui_instance The TGUI Gui object to display the splash screen in
     * @param duration The duration of the splash screen in seconds
     */
    void display(const tgui::Gui& gui_instance, float duration);

private:
    /**
     * Reset the position of the entities.
     *
     * This method reset the position of the splash screen entities by modifying
     * the m_position_map property. It is used by display method when the user resize
     * the window to rearrange the entities position
     *
     * @param window_size the new size of the window
     */
    void m_remap(const sf::Vector2u& window_size);

    /**
     * Draw all the entities of the splash screen.
     *
     * This method draw each entity/sprite of the splash screen
     * in the correct position
     *
     * @param render_target the render target where draw entities
     * @param sprite the sprite to draw
     * @param alpha the transparency layer to apply
     */
    void m_draw(sf::RenderTarget* render_target, sf::Sprite& sprite, sf::Uint8 alpha);

    /**
     * The SFML texture object containing the sprite
     */
    sf::Texture& m_texture;

    /**
     * The SFML IntRect object defining the coordinates of the part of the sprite to use as the splash screen
     */
    std::map<SpritePosition, sf::IntRect> m_map;

    /**
     * The SFML Vector2u object containing the size of the window
     */
    sf::Vector2u m_window_size;

    /**
     * The value of each position of the mapping
     */
    std::map<SpritePosition, sf::Vector2f> m_position_map;
};

#endif //SPLASHSCREEN_H
