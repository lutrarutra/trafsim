#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Timer.hpp"
#include "Map.hpp"

namespace TrafSim
{

class Application
{
public:
    Application(int width, int height, const std::string &title, const sf::ContextSettings &settings);
    void run();
    void exit();


private:
    Window window_;
    Map map_;
    Timer tick_timer_;
    //Ticks per second
    const unsigned int ticks_ps_ = 20;
    //Seconds per tick
    const float seconds_pt_;
    //float array initialized all elements with 0
    float fps_array_[120]{};
    //console stuff
    std::vector<std::string> console_strings_;

public:
    static void HandleEvent(const sf::Event &ev);
    static Application* GetInstance();
private:
    static Application* App_Instance;
    static std::vector<sf::Keyboard::Key> keys_pressed_;
    static std::vector<sf::Mouse::Button> btns_pressed_;

};

} // namespace TrafSim
