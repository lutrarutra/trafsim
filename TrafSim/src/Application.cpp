#include <iostream>
#include <memory>

#include "Application.hpp"
#include "GUI.hpp"
#include "Car.hpp"

namespace TrafSim
{

Application::Application(int width, int height, const std::string &title, const sf::ContextSettings &settings)
    : window_(width, height, title, settings), map_(), seconds_pt_(1000.0f / (1.0f * ticks_ps_))
{
    window_.setClearColor(sf::Color::Black);
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
                fps_array_[i] = fps_array_[i-1];
            }
            frame_counter = 0;
            fps_timer.reset();
        }

        window_.pollEvent();
        window_.clear();
        GUI::performance_monitor(fps_array_);
        GUI::console(line, console_strings_);
        map_.draw(window_);
        window_.display();

        frame_counter++;
    }
    exit();
}

void Application::exit()
{
    ImGui::SFML::Shutdown();
}

} // namespace TrafSim