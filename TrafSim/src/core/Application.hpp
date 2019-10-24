#pragma once

#include <SFML/Graphics.hpp>

#include "trafsim/Map.hpp"
#include "util/Timer.hpp"

namespace TrafSim
{

class Application
{
public:
    Application(int width, int height, const std::string &title, const sf::ContextSettings &settings);
    void run(const char* argv);
    void exit();
    void handleEvent(const sf::Event &ev);
    void handleInputBuffers(const float deltatime, const sf::Vector2i& delta_mp);

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
    sf::Vector2f m_mousePos;

    //Our program can put maximum of 5 key events to boffer
    bool m_keyBuffer[sf::Keyboard::KeyCount]{false};
    bool m_buttonBuffer[sf::Mouse::ButtonCount]{false};

    //Static members
public:
    static Application *GetInstance();

private:
    static Application *S_AppInstance;
};

} // namespace TrafSim
