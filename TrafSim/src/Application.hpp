#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Timer.hpp"

namespace TrafSim
{

class Application
{
public:
    Application(int width, int height, const std::string &title, const sf::ContextSettings &settings);
    void run();

private:
    Window window_;
    Timer tick_timer_;
    //Ticks per second
    const unsigned int ticks_ps_ = 20;
    //Seconds per tick
    const float seconds_pt_;
};

} // namespace TrafSim
