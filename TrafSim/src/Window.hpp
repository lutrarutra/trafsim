#pragma once

#include <string>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>


namespace TrafSim
{
class Window
{
public:
    Window(int width, int height, const std::string &title, const sf::ContextSettings &settings);
    void setClearColor(const sf::Color &color);
    void pollEvent();
    const sf::Color &get_clear_color() const { return clear_color_; }

    //Getters
    unsigned int getWidth() { return window_.getSize().x; }
    unsigned int getHeight() { return window_.getSize().y; }
    bool isOpen() const { return window_.isOpen(); }

    //rendering stuff
    void draw(const sf::Shape &shape);
    void clear();
    void display();
    void close();

private:
    void zoomView(sf::Vector2i relative_to, float zoom);
    
private:
    sf::RenderWindow window_;
    sf::View map_view_;
    sf::Color clear_color_;
    sf::Clock clock_;
    float zoom_ = 1;
    char title_[255];

};

} // namespace TrafSim
