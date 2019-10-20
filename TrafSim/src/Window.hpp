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
    bool isOpen() const { return window_.isOpen(); }
    void close();
    void clear();
    void draw(const sf::Shape &shape);
    void display();
    void pollEvent();
    const sf::Color &get_clear_color() const { return clear_color_; }
    unsigned int get_width() { return window_.getSize().x; }
    unsigned int get_height() { return window_.getSize().y; }

private:
    sf::RenderWindow window_;
    sf::Color clear_color_;
    sf::Clock clock_;
    char title_[255];
};

} // namespace TrafSim
