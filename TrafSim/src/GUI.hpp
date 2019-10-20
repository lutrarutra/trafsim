#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Window.hpp"

namespace TrafSim
{

//Static class we can create our windows here
class GUI
{
public:
    //Color picker
    static sf::Color color_picker(const sf::Color &color_)
    {
        sf::Color clr = color_;
        float color[4];
        color[0] = clr.r / 255.0f;
        color[1] = clr.g / 255.0f;
        color[2] = clr.b / 255.0f;
        color[3] = clr.a / 255.0f;
        ImGui::Begin("Sample window");
        ImGui::SetWindowFontScale(2.5f);
        if (ImGui::ColorEdit4("Select color", color))
        {
            // this code gets called if color value changes, so
            // the background color is upgraded automatically!
            clr.r = static_cast<sf::Uint8>(color[0] * 255.f);
            clr.g = static_cast<sf::Uint8>(color[1] * 255.f);
            clr.b = static_cast<sf::Uint8>(color[2] * 255.f);
            clr.a = static_cast<sf::Uint8>(color[3] * 255.f);
        }
        ImGui::End();
        return clr;
    }
};

} // namespace TrafSim
