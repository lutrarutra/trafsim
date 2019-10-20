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
        ImGui::Begin("Color picker");
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

    static std::string console(const std::string& str)
    {
        char buffer[255];
        strcpy(buffer, str.c_str());
        ImGui::Begin("Console");
        ImGui::SetWindowFontScale(2.5f);
        ImGui::InputText("Console", buffer, 255);
        if(ImGui::Button("Enter") || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            memset(buffer, 0, 255);
        }
        ImGui::End();
        return std::string(buffer);
    }
};

} // namespace TrafSim
