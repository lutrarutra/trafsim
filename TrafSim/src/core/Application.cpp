#include <iostream>
#include <memory>
#include <algorithm>
#include <thread>

#include "Application.hpp"
#include "util/GUI.hpp"

#include "trafsim/Car.hpp"

namespace TrafSim
{

// These will be only available in this file because they are private static members of Application
Application *Application::S_AppInstance = nullptr;

// We can only have one instance of a application and it is stored
Application::Application(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : m_window(width, height, title, settings)
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
    Timer fps_timer;
    std::string line = "";
    unsigned int frame_counter = 0;

    // auto n1 = std::make_shared<Node>(sf::Vector2f(100, 1000));
    // auto n2 = std::make_shared<Node>(sf::Vector2f(600, 1000));

    // auto n3 = std::make_shared<Node>(sf::Vector2f(600, 500));
    // auto n4 = std::make_shared<Node>(sf::Vector2f(100, 500));

    // auto n5 = std::make_shared<Node>(sf::Vector2f(1000, 500));
    // auto n6 = std::make_shared<Node>(sf::Vector2f(1000, 1000));

    // auto n7 = std::make_shared<Node>(sf::Vector2f(1500, 1000));
    // auto n8 = std::make_shared<Node>(sf::Vector2f(1500, 500));

    // n1->connect(n2);
    // n3->connect(n4);
    // n5->connect(n6);
    // n7->connect(n8);

    // m_map.createRoads(n1);
    // m_map.createRoads(n3);
    // m_map.createRoads(n5);
    // m_map.createRoads(n7);

    auto n1 = std::make_shared<Node>(sf::Vector2f(1000, 500));
    auto n2 = std::make_shared<Node>(sf::Vector2f(1000, 1500));

    auto n3 = std::make_shared<Node>(sf::Vector2f(500, 1000));
    auto n4 = std::make_shared<Node>(sf::Vector2f(1500, 1000));

    n1->connect(n2);
    n3->connect(n4);
    m_map.createRoads(n1);
    m_map.createRoads(n3);
    m_map.checkIntersections();

    m_map.addCar(n2);
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
            m_map.update(m_tickTimer.msFromReset<float>());
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
        handleInputBuffers(fps_timer.msFromReset<float>(), delta_mp - sf::Mouse::getPosition());
        delta_mp = sf::Mouse::getPosition();
        m_window.clear();
        //IamGui stuff
        GUI::performance_monitor(fps_array_);
        GUI::console(line, m_console_strings);
        m_map.draw(m_window);
        m_window.display();
        frame_counter++;
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
        if (ev.mouseButton.button == sf::Mouse::Left)
            m_buttonBuffer[ev.mouseButton.button] = false;
        break;
    case sf::Event::MouseWheelScrolled:
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
    if (m_buttonBuffer[sf::Mouse::Left])
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