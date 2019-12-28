#include "Application.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <utility>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

#include "trafficsim/RoadTile.hpp"
#include "trafficsim/StraightRoad.hpp"
#include "trafficsim/RoadIntersection.hpp"
#include "trafficsim/RoadTrisection.hpp"
#include "trafficsim/RoadJunction.hpp"
#include "trafficsim/HomeRoad.hpp"
#include "trafficsim/HomeBuilding.hpp"

namespace ts
{

Application *Application::AppInstance = nullptr;

Application::Application()
    : builder_(map_, window_), statistics_(map_, window_, logs_), time_line_(map_), data_(logs_)
{
    AppInstance = this;
    data_.loadTexturesFromFile("texture_list.txt");
    StraightRoad::SetTexture(data_.getTexture("straight_road"));
    HomeRoad::SetTexture(data_.getTexture("home_road"));
    RoadTurn::SetTextures(data_.getTexture("right_turn"), data_.getTexture("left_turn"));
    RoadIntersection::SetTextures(data_.getTexture("right_intersection"), data_.getTexture("left_intersection"));
    RoadTrisection::SetTextures(data_.getTexture("right_trisection"), data_.getTexture("left_trisection"));
    RoadJunction::SetTextures(data_.getTexture("right_junction"), data_.getTexture("left_junction"));
    Car::AddTexture(data_.getTexture("blue_car"));
    Car::AddTexture(data_.getTexture("brown_car"));
    Car::AddTexture(data_.getTexture("green_car"));
    Car::AddTexture(data_.getTexture("grey_car"));
    Car::AddTexture(data_.getTexture("white_car"));
    Car::AddTexture(data_.getTexture("red_car"));
    Car::AddTexture(data_.getTexture("teal_car"));
    HomeBuilding::SetTexture(data_.getTexture("home_building"));
    OfficeBuilding::SetTexture(data_.getTexture("office_building"));
    window_.setViewPos({map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount() / 2, map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount() / 2});
    window_.setZoom(3.f);
}

void Application::run()
{
    float last_time = time_line_.getRealTime();
    sf::Vector2i delta_mouse_pos = sf::Mouse::getPosition();

    //Main loop
    while (window_.isOpen())
    {
        window_.pollEvent();

        map_.update(time_line_.getGameTime(), time_line_.getFrameTime() * time_line_.getMultiplier());
        time_line_.update(app_state_ == State::Simulating);

        handleInputBuffers(delta_mouse_pos - sf::Mouse::getPosition());
        delta_mouse_pos = sf::Mouse::getPosition();

        window_.clear();
        //Drawing happens between window.clear() and window.draw()
        window_.draw(map_);
        drawGUI();
        window_.display();
    }
}

void Application::changeState(State new_state)
{
    app_state_ = new_state;
    switch (app_state_)
    {
    case Editing:
        builder_.setBuildingMode(true);
        map_.setSimulating(false);
        break;
    case Simulating:
        builder_.setBuildingMode(false);
        map_.setSimulating(true);
        break;
    default:
        break;
    }
}

const char *state_mode(State state)
{
    return (const char *[]){
        "Editing",
        "Simulating"}[state];
}

void Application::drawGUI()
{
    ImGui::Begin("Log");
    ImGui::BeginChild("");
    for (unsigned int i = logs_.size(); i > 0; --i)
    {
        ImGui::Text("Log: %s", logs_[i - 1].c_str());
    }
    ImGui::EndChild();
    ImGui::End();
    if (app_state_ == Simulating)
    {
        time_line_.drawGUI();
        statistics_.drawGUI();
        drawHeatMap();
    }
    if (app_state_ == Editing)
        builder_.drawGUI();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            static char buf[32];
            const char *c;
            std::string file_name;
            ImGui::InputText("Filename", buf, IM_ARRAYSIZE(buf));

            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
            {
                file_name = buf + std::string(".csv");
                c = file_name.c_str();
                data_.loadMap(c, builder_, map_.grid_);
            }
            if (ImGui::MenuItem("Load", "Enter"))
            {
                file_name = buf + std::string(".csv");
                c = file_name.c_str();
                data_.loadMap(c, builder_, map_.grid_);
            }
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                // ".ts" for traffic sim :)
                file_name = buf + std::string(".csv");
                c = file_name.c_str();
                data_.saveMap(c, map_.grid_);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Mode"))
        {
            for (int i = 0; i < State::StateCount; i++)
            {
                State new_state = static_cast<State>(i);
                if (ImGui::MenuItem(state_mode(new_state), "", app_state_ == new_state))
                    changeState(new_state);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Scale"))
        {
            if (ImGui::MenuItem("Scale: 100%", "Ctrl+1", ImGui::GetFont()->Scale == 1.f))
                ImGui::GetFont()->Scale = 1.f;
            if (ImGui::MenuItem("Scale: 125%", "Ctrl+2", ImGui::GetFont()->Scale == 1.25f))
                ImGui::GetFont()->Scale = 1.25f;
            if (ImGui::MenuItem("Scale: 150%", "Ctrl+3", ImGui::GetFont()->Scale == 1.5f))
                ImGui::GetFont()->Scale = 1.5f;
            if (ImGui::MenuItem("Scale: 200%", "Ctrl+4", ImGui::GetFont()->Scale == 2.f))
                ImGui::GetFont()->Scale = 2.f;
            if (ImGui::MenuItem("Scale: 250%", "Ctrl+5", ImGui::GetFont()->Scale == 2.5f))
                ImGui::GetFont()->Scale = 2.5f;
            if (ImGui::MenuItem("Scale: 300%", "Ctrl+6", ImGui::GetFont()->Scale == 3.f))
                ImGui::GetFont()->Scale = 3.f;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Application::drawHeatMap()
{
    ImGui::Begin("Heat map");
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    ImVec2 canvas_pos = ImGui::GetCursorScreenPos();     // ImDrawList API uses screen coordinates!
    ImVec2 canvas_size = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
    if (canvas_size.x < 50.0f)
        canvas_size.x = 50.0f;
    if (canvas_size.y < 50.0f)
        canvas_size.y = 50.0f;

    draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.x), IM_COL32(119, 160, 93, 180));
    draw_list->AddRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.x), IM_COL32(255, 255, 255, 255));

    // Map view
    // at the end canvas_size.x on purpose to get square
    float canvas_view_w = window_.getView().getSize().x / (map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount()) * canvas_size.x;
    float canvas_view_h = window_.getView().getSize().y / (map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount()) * canvas_size.x;
    float canvas_view_x = {window_.getView().getCenter().x / (map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount()) * canvas_size.x};
    float canvas_view_y = {window_.getView().getCenter().y / (map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount()) * canvas_size.x};
    sf::Vector2f view_pos_min = {canvas_view_x - canvas_view_w / 2 + canvas_pos.x, canvas_view_y - canvas_view_h / 2 + canvas_pos.y};
    sf::Vector2f view_pos_max = {canvas_view_x + canvas_view_w / 2 + canvas_pos.x, canvas_view_y + canvas_view_h / 2 + canvas_pos.y};
    draw_list->AddRect(view_pos_min, view_pos_max, IM_COL32(255, 255, 255, 255), 0, 15.f, 5.0f);

    float canvas_tile_size = canvas_size.x / map_.grid_.getSideCount();
    const unsigned int time_window = 24 * 60 * 60 / 96;
    float g_time = time_line_.getGameTime().asSeconds();
    unsigned int time_index = g_time / time_window;
    float time_passed = (g_time / time_window - (int)(g_time / time_window)) * time_window;

    const int max_cars_per_sample = 500;

    // No std::tuple
    struct TileSample
    {
        TileSample(const ImVec2 &p1, const ImVec2 &p2, const sf::Color &c)
            : p1(p1), p2(p2), c(c){};

        const ImVec2 p1;
        const ImVec2 p2;
        const sf::Color c;
    };

    // Heatmap
    for (unsigned int i = 0; i < map_.grid_.getTotalTileCount(); ++i)
    {
        if (map_.grid_.getTile(i)->getCategory() == TileCategory::RoadCategory)
        {
            sf::Vector2f p_min = {(i % map_.grid_.getSideCount()) * canvas_tile_size + canvas_pos.x, int(i / map_.grid_.getSideCount()) * canvas_tile_size + canvas_pos.y};
            sf::Vector2f p_max = p_min + sf::Vector2f(canvas_tile_size, canvas_tile_size);
            std::uint16_t car_count = map_.grid_.getTile(i)->getNode()->getCarsPassed().at(time_index);
            draw_list->AddRectFilled(p_min, p_max, IM_COL32(26, 26, 26, 255));

            float heat_color = 255 - (car_count * time_window / time_passed) / max_cars_per_sample * 255;
            if (heat_color > 0)
                draw_list->AddRectFilled(p_min, p_max, IM_COL32(255, heat_color, heat_color, heat_color));
        }
        if (map_.grid_.getTile(i)->getCategory() == TileCategory::BuildingCategory)
        {
            sf::Vector2f p_min = {(i % map_.grid_.getSideCount()) * canvas_tile_size + canvas_pos.x, int(i / map_.grid_.getSideCount()) * canvas_tile_size + canvas_pos.y};
            sf::Vector2f p_max = p_min + sf::Vector2f(canvas_tile_size, canvas_tile_size);
            draw_list->AddRectFilled(p_min, p_max, IM_COL32(47, 58, 224, 255));
            map_.grid_.getTile(i)->getNode()->getCarsPassed().at(time_index);
        }
    }

    bool adding_preview = false;
    ImGui::InvisibleButton("canvas", canvas_size);
    sf::Vector2f mouse_pos_in_canvas = sf::Vector2f(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);

    if (ImGui::IsItemHovered())
    {
        if (ImGui::IsMouseDown(0))
        {
            sf::Vector2f new_center = (mouse_pos_in_canvas / canvas_size.x) * (map_.grid_.getTile(0)->getSize() * map_.grid_.getSideCount());
            window_.setViewPos(new_center);
        }
    }
    draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), true); // clip lines within the canvas (if we resize it, etc.)
    draw_list->PopClipRect();

    ImGui::End();
}

void Application::handleEvent(const sf::Event &ev)
{
    builder_.handleInput(ev);
    statistics_.handleInput(ev);
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        key_buffer_[ev.key.code] = true;
        break;
    case sf::Event::KeyReleased:
        key_buffer_[ev.key.code] = false;
        break;
    case sf::Event::MouseButtonPressed:
        button_buffer_[ev.mouseButton.button] = true;
        break;
    case sf::Event::MouseButtonReleased:
        button_buffer_[ev.mouseButton.button] = false;
        break;
    default:
        break;
    }
    // Shortcuts
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Num1 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.f;
        else if (ev.key.code == sf::Keyboard::Num2 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.25f;
        else if (ev.key.code == sf::Keyboard::Num3 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 1.5f;
        else if (ev.key.code == sf::Keyboard::Num4 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.f;
        else if (ev.key.code == sf::Keyboard::Num5 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 2.5f;
        else if (ev.key.code == sf::Keyboard::Num6 && key_buffer_[sf::Keyboard::LControl])
            ImGui::GetFont()->Scale = 3.f;

        else if (ev.key.code == sf::Keyboard::S && key_buffer_[sf::Keyboard::LControl])
            data_.saveMap(data_.getCurrentFileName(), map_.grid_);
        else if (ev.key.code == sf::Keyboard::O && key_buffer_[sf::Keyboard::LControl])
        {
            //data_.loadMap("test.csv", builder_, map_.grid_);
        }

        else if (ev.key.code == sf::Keyboard::Up && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = {1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f};
            if (window_.gui_zoom_index < 5)
            {
                window_.gui_zoom_index++;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
        else if (ev.key.code == sf::Keyboard::Down && key_buffer_[sf::Keyboard::LShift])
        {
            float zoom_vals[6] = {1.f, 1.25, 1.5f, 2.f, 2.5f, 3.f};
            if (window_.gui_zoom_index > 0)
            {
                window_.gui_zoom_index--;
                ImGui::GetFont()->Scale = zoom_vals[window_.gui_zoom_index];
            }
        }
    }
}

void Application::handleInputBuffers(const sf::Vector2i &delta_mp)
{
    // LEFT mouse button is pressed down
    if (button_buffer_[sf::Mouse::Left])
    {
        // store temporarily selected "radio button" option such as "Add Road"

        // if left control is down add a road
        if (key_buffer_[sf::Keyboard::LControl] && app_state_ == Editing)
            builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), AddRoad);

        // if left shift is down remove road or building
        else if (key_buffer_[sf::Keyboard::LShift] && app_state_ == Editing)
            builder_.slideAction(window_.convert(sf::Mouse::getPosition(window_.getWindow())), Remove);

        // if no control or shift keys pressed move map
        else
        {
            window_.moveView(delta_mp);
        }
    }
}

void Application::close()
{
    ImGui::SFML::Shutdown();
}

Application *Application::GetInstance()
{
    return AppInstance;
}

} // namespace ts
