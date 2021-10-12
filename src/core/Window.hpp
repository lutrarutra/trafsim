#pragma once

#include <SFML/Graphics.hpp>

namespace ts
{
class Window
{
public:
    Window();

    //Getters
    const sf::Window &getWindow() const { return window_; }
    const sf::View &getView() const { return view_; }
    int getWidth() const { return window_.getSize().x; }
    int getHeight() const { return window_.getSize().y; }
    bool isOpen() const { return window_.isOpen(); }
    bool isGuiHovered() const;

    // Converts point on map to point on screen (coordinate -> pixel)
    sf::Vector2i convert(const sf::Vector2f &point) const { return window_.mapCoordsToPixel(point); }
    // Converts point on screen to point on map (pixel -> coordinate)
    sf::Vector2f convert(const sf::Vector2i &point) const { return window_.mapPixelToCoords(point); }

    // moves view when left mb is pressed and moved
    void moveView(const sf::Vector2i &delta_pos);
    // For moving map with heatmap
    void setViewPos(const sf::Vector2f &pos);

    void setZoom(float zoom);


    // polls events from SFML
    void pollEvent();

    // For rendering stuff on the screen
    void draw(const sf::Drawable &obj) { window_.draw(obj); };
    void clear();
    void display();

    int gui_zoom_index = 3;

private:
    void zoomView(const sf::Vector2i &relative_to, float zoom);

private:
    sf::RenderWindow window_;
    sf::Clock clock_;
    sf::View view_;
    float zoom_ = 1.f;
};
} // namespace ts
