#include <iostream>
#include <memory>
#include <algorithm>

#include "Application.hpp"
#include "GUI.hpp"
#include "Car.hpp"

namespace TrafSim
{

// These will be only available in this file because they are private static members of Application
Application *Application::App_Instance = nullptr;
std::vector<sf::Keyboard::Key> Application::keys_pressed_;
std::vector<sf::Mouse::Button> Application::btns_pressed_;

// We can only have one instance of a application and it is stored
Application::Application(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(width, height, title, settings), map_(), seconds_pt_(1000.0f / (1.0f * ticks_ps_))
{
    App_Instance = this;
}

//Main loop of the engine
void Application::run()
{
    unsigned int ticks = 0;
    //Time since last update in milliseconds
    float lag = 0;
    Timer game_timer;
    map_.add_entity(std::make_shared<Car>(Car()));
    std::string line = "";
    Timer fps_timer;
    unsigned int frame_counter = 0;

    sf::Texture texture;
    if (!texture.loadFromFile("worldmap.png"))
        std::cout << "Could not find it" << std::endl;

    sf::RectangleShape rect(sf::Vector2f(window_.get_width(), window_.get_height()));

    rect.setTexture(&texture);

    while (window_.isOpen())
    {

        //This code will be executed on fixed time intervals
        if (tick_timer_.msFromReset<float>() - lag > seconds_pt_)
        {
            ticks++;
            //We need to remove little lag from our timer so it won't stack it
            lag -= tick_timer_.msFromReset<float>() - seconds_pt_;
            tick_timer_.reset();
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

        window_.pollEvent(HandleEvent);
        window_.clear();
        GUI::performance_monitor(fps_array_);
        GUI::console(line, console_strings_);
        map_.draw(window_);
        window_.draw(rect);
        window_.display();
        frame_counter++;
    }
    exit();
}

bool contains(const std::vector<sf::Keyboard::Key> vec, const sf::Keyboard::Key &element)
{
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

void Application::HandleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (contains(Application::keys_pressed_, ev.key.code))
            Application::keys_pressed_.push_back(ev.key.code);
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
    return App_Instance;
}

void Application::exit()
{
    ImGui::SFML::Shutdown();
}

} // namespace TrafSim