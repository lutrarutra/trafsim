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
    void handleEvent(const sf::Event &ev);

private:
    Window m_window;
    Map m_map;
    Timer m_tickTimer;
    //Ticks per second
    const unsigned int m_tickPerSecond = 20;
    //Seconds per tick
    const float m_secondsPerTick = 1000.0f / (1.0f * m_tickPerSecond);
    //float array initialized all elements with 0
    float fps_array_[120]{};
    //console stuff
    std::vector<std::string> m_console_strings;
    std::vector<sf::Keyboard::Key> m_keyBuffer;
    std::vector<sf::Mouse::Button> m_buttonBuffer;

    //Static members
public:
    static Application *GetInstance();

private:
    static Application *S_AppInstance;
};

} // namespace TrafSim
