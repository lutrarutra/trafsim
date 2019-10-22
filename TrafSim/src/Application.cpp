#include <iostream>
#include <memory>
#include <algorithm>

#include "Application.hpp"
#include "GUI.hpp"
#include "Car.hpp"

namespace TrafSim
{

// These will be only available in this file because they are private static members of Application
Application *Application::S_AppInstance = nullptr;

// We can only have one instance of a application and it is stored
Application::Application(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : m_window(width, height, title, settings), m_map()
{
    S_AppInstance = this;
}

//Main loop of the engine
void Application::run()
{
    unsigned int ticks = 0;
    //Time since last update in milliseconds
    float lag = 0;
    Timer game_timer;
    m_map.add_entity(std::make_shared<Car>(Car()));
    std::string line = "";
    Timer fps_timer;
    unsigned int frame_counter = 0;

    sf::Texture texture;
    if (!texture.loadFromFile("worldmap.png"))
        std::cout << "Could not find it" << std::endl;

    sf::RectangleShape rect(sf::Vector2f(m_window.getWidth(), m_window.getHeight()));

    rect.setTexture(&texture);

    while (m_window.isOpen())
    {

        //This code will be executed on fixed time intervals
        if (m_tickTimer.msFromReset<float>() - lag > m_secondsPerTick)
        {
            ticks++;
            //We need to remove little lag from our timer so it won't stack it
            lag -= m_tickTimer.msFromReset<float>() - m_secondsPerTick;
            m_tickTimer.reset();
        }
        //Calculate and update fps each 100ms
        if (fps_timer.msFromReset<float>() > 100)
        {
            float fps = 1000 * frame_counter / fps_timer.msFromReset<float>();
            fps_array_[0] = fps;
            for (int i = 119; i > 0; --i)
            {
                fps_array_[i] = fps_array_[i - 1];
            }
            frame_counter = 0;
            fps_timer.reset();
        }

        m_window.pollEvent();
        m_window.clear();
        GUI::performance_monitor(fps_array_);
        GUI::console(line, m_console_strings);
        m_map.draw(m_window);
        m_window.draw(rect);
        m_window.display();
        frame_counter++;
    }
    exit();
}

bool contains(const std::vector<sf::Keyboard::Key> vec, const sf::Keyboard::Key &element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

void Application::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (contains(m_keyBuffer, ev.key.code))
            m_keyBuffer.push_back(ev.key.code);
        break;
    case sf::Event::KeyReleased:
        break;
    case sf::Event::MouseButtonPressed:
        break;
    case sf::Event::MouseButtonReleased:
        break;
    default:
        break;
    }
}

Application *Application::GetInstance()
{
    return S_AppInstance;
}

void Application::exit()
{
    ImGui::SFML::Shutdown();
}

} // namespace TrafSim