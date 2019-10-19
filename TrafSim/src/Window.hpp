#pragma once

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace TrafSim
{
class Window
{
public:
    Window(int width, int height, const std::string &title, const sf::ContextSettings &settings);
    void setClearColor(const sf::Color &color);
    bool isOpen() const { return window_.isOpen(); }
    void close() { window_.close(); }
    void clear() { window_.clear(clear_color_); }
    void draw(const sf::Shape &shape);
    void display() { window_.display(); }
    void pollEvent();
    unsigned int get_width() { return window_.getSize().x; }
    unsigned int get_height() { return window_.getSize().y; }

private:
    sf::RenderWindow window_;
    sf::Color clear_color_;
};

} // namespace TrafSim
