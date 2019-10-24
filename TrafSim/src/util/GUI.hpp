#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "Window.hpp"

namespace TrafSim
{
//Because it is static it will be only visible in this file
//Kinda like a private
static float fps_lim = 0;

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

    static void console(std::string &str, std::vector<std::string> &console_output)
    {
        char buffer[255];
        strcpy(buffer, str.c_str());
        ImGui::Begin("Console");
        bool focused = true;
        //When window appears it will set keyboard focus to it
        if(ImGui::GetCurrentWindow()->Appearing)
        {
            ImGui::SetKeyboardFocusHere();
        }
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputText("", buffer, 255);
        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
        {
            console_output.emplace_back(buffer);
            memset(buffer, 0, 255);
            focused = false;
        }
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console");
        ImGui::BeginChild("");
        for (unsigned long i = 0; i < console_output.size(); ++i)
            ImGui::Text("TrafSim: %s", console_output[i].c_str());
        ImGui::EndChild();
    
        //if enter was pressed focused was set to false
        //it will now set focus back to input field
        //So we can continue to put commands
        ImGui::SetItemDefaultFocus();
        if (!focused)
        {
            ImGui::SetKeyboardFocusHere(-1);
        }
        ImGui::End();
        str = buffer;
    }

    //Store fps values of last minute (one fps value, half a second)
    static void performance_monitor(const float *fps_array)
    {
        if(fps_lim < fps_array[0])
            fps_lim = (fps_array[0]) * 1.1f;
        char buffer[255];
        ImGui::Begin("Performance monitor");
        ImGui::Text("FPS: %.f", fps_array[0]);
        int x = ImGui::GetContentRegionAvail().x;
        int y = ImGui::GetContentRegionAvail().y;
        ImGui::PlotLines("", fps_array, 119, 0, NULL, 0, fps_lim, ImVec2(x, y));
        ImGui::End();
    }

    static void progress_bar(const float progress, const char* name)
    {
        ImGui::Begin(name);
        ImGui::ProgressBar(progress);
        ImGui::End();
    }
};

} // namespace TrafSim
