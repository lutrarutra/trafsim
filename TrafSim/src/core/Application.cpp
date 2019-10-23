#include <iostream>
#include <memory>
#include <algorithm>

#include "util/OsmHandler.hpp"
#include "util/Random.hpp"
#include "Application.hpp"
#include "util/GUI.hpp"
#include "Car.hpp"
#include "Building.hpp"

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
void Application::run(const char *argv)
{
    unsigned int ticks = 0;
    //Time since last update in milliseconds
    float lag = 0;
    Timer game_timer;
    std::string line = "";
    Timer fps_timer;
    unsigned int frame_counter = 0;

    // sf::Texture texture;
    // if (!texture.loadFromFile("worldmap.png"))
    //     std::cout << "Could not find it" << std::endl;

    // sf::RectangleShape rect(sf::Vector2f(m_window.getWidth(), m_window.getHeight()));
    // rect.setTexture(&texture);

    //All this to create building
    OsmHandler osm(argv, m_window);
    {
        PerformanceTimer p;
        
        unique_vector a = osm.FindBuildings();
        m_map.addEntities(a);
        // With unique pointers it took us 157ms
    }


    //Keep track of mouse movement between each frame (delta_mouseposition)
    sf::Vector2i delta_mp = sf::Mouse::getPosition();

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

        //IamGui stuff
        GUI::performance_monitor(fps_array_);
        GUI::console(line, m_console_strings);
        m_map.draw(m_window);
        //m_window.draw(rect);

        m_window.display();
        frame_counter++;
        handleInputBuffers(fps_timer.msFromReset<float>(), delta_mp - sf::Mouse::getPosition());
        delta_mp = sf::Mouse::getPosition();
    }
    exit();
}

void Application::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        m_keyBuffer[ev.key.code] = true;
        break;
    case sf::Event::KeyReleased:
        m_keyBuffer[ev.key.code] = false;
        break;
    case sf::Event::MouseButtonPressed:
        m_buttonBuffer[ev.mouseButton.button] = true;
        break;
    case sf::Event::MouseButtonReleased:
        m_buttonBuffer[ev.mouseButton.button] = false;
        break;
    default:
        break;
    }
}

void Application::handleInputBuffers(const float deltatime, const sf::Vector2i &delta_mp)
{
    //Arrow keys
    if (m_keyBuffer[sf::Keyboard::Up])
        m_window.moveView(0, -deltatime);
    if (m_keyBuffer[sf::Keyboard::Down])
        m_window.moveView(0, deltatime);
    if (m_keyBuffer[sf::Keyboard::Right])
        m_window.moveView(deltatime, 0);
    if (m_keyBuffer[sf::Keyboard::Left])
        m_window.moveView(-deltatime, 0);

    //Mouse buttons
    if (m_buttonBuffer[sf::Mouse::Middle])
        m_window.moveViewWithMouse(delta_mp);
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