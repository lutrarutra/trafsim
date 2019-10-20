#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Window.hpp"

namespace TrafSim
{

//Static struct we can create our windows here
class GUI
{
public:
    static void color_picker()
    {
        ImGui::Begin("Sample window");
        ImGui::SetWindowFontScale(2.5f);
        ImGui::Button("Hello, ImGui!");
        ImGui::End();
    }
};

} // namespace TrafSim
