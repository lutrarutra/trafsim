#include "Statistics.hpp"

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace ts
{
Statistics::Statistics(Map &map, const Window &window, std::vector<std::string> &logs) : map_(map), window_(window), logs_(logs){};

void Statistics::drawGUI()
{
    if (selected_tile_index_ != UINT_MAX && map_.grid_.getTile(selected_tile_index_)->getCategory() == RoadCategory)
    {
        const auto &node_data = map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed().data();
        std::size_t data_size = map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed().size();
        constexpr float SCALE_MAX = 300.f;
        constexpr float SCALE_MIN = 0.f;

        // Getter to convert std::uin16_t array to float array
        static auto getter = [](void *data, int idx) -> float {
            std::uint16_t *values = (std::uint16_t *)(data);
            return (float)(values[idx]);
        };

        ImGui::Begin("Statistics");
        if (ImGui::Button("Export"))
        {
            exportCSV("histogram.csv", map_.grid_.getTile(selected_tile_index_)->getNode()->getCarsPassed());
        };

        int x = ImGui::GetContentRegionAvail().x;
        int y = ImGui::GetContentRegionAvail().y;
        ImGui::PlotHistogram("Histogram", getter, (void *)node_data, data_size, 0, "Number of Vehicles", SCALE_MIN, SCALE_MAX, ImVec2(x, y));
        ImGui::End();
    }
}

void Statistics::selectTile(const sf::Vector2f &pos)
{
    auto new_tile = map_.grid_.getTile(pos);
    if (!new_tile)
    {
        unSelectTile();
        return;
    }
    if (new_tile->getTileIndex() == selected_tile_index_)
    {
        new_tile->unSelectTile();
        selected_tile_index_ = UINT_MAX;
    }
    else
    {
        new_tile->selectTile();
        unSelectTile();
        selected_tile_index_ = new_tile->getTileIndex();
    }
}

void Statistics::unSelectTile()
{
    if (selected_tile_index_ != UINT_MAX)
        map_.grid_.getTile(selected_tile_index_)->unSelectTile();
    selected_tile_index_ = UINT_MAX;
}

void Statistics::handleInput(const sf::Event &ev)
{
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (window_.isGuiHovered())
            return;
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            unSelectTile();
        }
        else if (ev.mouseButton.button == sf::Mouse::Left)
        {
            selectTile(pos);
        }
    }
}

void Statistics::exportCSV(const char *file_name, const std::vector<std::uint16_t> &car_data)
{
    std::cout << "Export histogram of amount of cars" << std::endl;
    FILE *fp = fopen(file_name, "w");
    for (auto i : car_data)
    {
        fprintf(fp, "%o,", i);
    }
    fclose(fp);
    std::cout << "Histogram data saved" << std::endl;
    logs_.emplace_back("Histogram data saved in " + std::string(file_name));
}

} // namespace ts