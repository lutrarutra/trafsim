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
    void moveViewWithMouse(const sf::Vector2i &delta_mp);
    void moveView(int dx, int dy);

    //Getters
    unsigned int getWidth() { return m_window.getSize().x; }
    unsigned int getHeight() { return m_window.getSize().y; }
    const sf::Color &getClearColor() const { return m_clearColor; }
    bool isOpen() const { return m_window.isOpen(); }

    //rendering stuff
    void draw(const sf::Drawable &obj);
    void clear();
    void display();
    void close();

private:
    void zoomView(sf::Vector2i relative_to, float zoom);

private:
    sf::RenderWindow m_window;
    sf::View m_mapView;
    sf::Color m_clearColor;
    sf::Clock m_clock;
    float m_zoom = 1;
    char m_title[255];
};

} // namespace TrafSim
