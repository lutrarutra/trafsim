#include "TimeLine.hpp"

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace ts
{

TimeLine::TimeLine(Map &map)
    : map_(map)
{
}

const sf::Time &TimeLine::getGameTime() const
{
    return game_time_;
}

float TimeLine::getRealTime() const
{
    return real_clock_.getElapsedTime().asSeconds();
}

float TimeLine::getFrameTime() const
{
    return frame_clock_.getElapsedTime().asSeconds();
}

void TimeLine::update(bool simulating)
{
    if (simulating)
    {
        game_time_ += frame_clock_.getElapsedTime() * multiplier_;
        if (game_time_.asSeconds() > 86400)
            restart();
    }
    frame_clock_.restart();
}

void TimeLine::restart()
{
    game_time_ = sf::seconds(0.f);
    map_.initDay();
}

void TimeLine::setMultiplier(float multiplier)
{
    multiplier_ = multiplier;
}

std::string TimeLine::timeToString() const
{
    int houres = (int)(game_time_.asSeconds() / 60 / 60) % 60;
    int minutes = (int)(game_time_.asSeconds() / 60) % 60;
    int seconds = (int)game_time_.asSeconds() % 60;
    return std::to_string(houres) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}

void TimeLine::drawGUI()
{
    float hours = game_time_.asSeconds() / 60 / 60;

    ImGui::Begin("Time");

    ImGui::Text(timeToString().c_str());
    // 25 is pretty much highest highest multiplier without encountering bugs
    ImGui::SliderFloat("Time scale", &multiplier_, 0.f, 25.f, "%.1f");
    ImGui::SliderFloat("Time", &hours, 0.f, 24.0f, "%.1f");
    if (hours * 60 * 60 > game_time_.asSeconds())
        game_time_ = sf::seconds(hours * 60 * 60);
    if (ImGui::Button("Reset Day"))
    {
        restart();
    }
    if (ImGui::Button("Morning"))
    {
        if (7 * 60 * 60 > game_time_.asSeconds())
            restart();
        game_time_ = sf::seconds(7 * 60 * 60);
    }
    if (ImGui::Button("Afternoon"))
    {
        if (15 * 60 * 60 > game_time_.asSeconds())
            restart();
        game_time_ = sf::seconds(15 * 60 * 60);
        map_.removeCars();
    }
    if (ImGui::Button("Hop 5min"))
    {
        game_time_ = game_time_ + sf::seconds(5 * 60);
        map_.removeCars();
    }
    if (ImGui::Button("Hop 15min"))
    {
        game_time_ = game_time_ + sf::seconds(15 * 60);
        map_.removeCars();
    }
    if (ImGui::Button("Hop 60min"))
    {
        game_time_ = game_time_ + sf::seconds(60 * 60);
        map_.removeCars();
    }
    if (game_time_.asSeconds() > 24 * 60 * 60)
    {
        restart();
    }
    ImGui::End();
}

} // namespace ts