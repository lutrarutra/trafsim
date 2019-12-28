#pragma once

#include <climits> // UINT_MAX
#include <string>
#include "Map.hpp"
#include "RoadTurn.hpp"
#include "StraightRoad.hpp"
#include "RoadIntersection.hpp"
#include "RoadTrisection.hpp"
#include "RoadJunction.hpp"
#include "TrafficLight.hpp"
#include "core/Window.hpp"
#include "BuildingTile.hpp"
#include "HomeRoad.hpp"
#include "IntersectionTemplates.hpp"
#include "HomeBuilding.hpp"
#include "OfficeBuilding.hpp"

namespace ts
{

enum EditingOption
{
    Inspect = 0,
    AddRoad,
    AddBuilding,
    AddTemplate,
    Remove,
    Rotate,
    Flip,
    AddLight,

    // Keep this as last
    ModeCount
};

class MapBuilder
{
public:
    MapBuilder(Map &map, const Window &window);

    // When App state is switched to "Editing"
    void setBuildingMode(bool val);

    // Handles mouse inputs to edit map
    void handleInput(const sf::Event &ev);

    // Editor GUI, drawed only when building_mode_ == true
    void drawGUI();

    // Sets all Tiles to Empty with Grid::init()
    void clearMap();

    // Adds a road
    void addRoad(const sf::Vector2f &pos, RoadType type, bool autorotate = true);
    void addBuilding(const sf::Vector2f &pos, BuildingType type);
    // When Left Control and left mousebutton pressed this gets called
    void slideAction(const sf::Vector2f &pos, EditingOption option);

    // Rotates roads 90 degrees clockwise
    void rotateRoad(const sf::Vector2f &pos);
    // Rotates flips roads
    void flipRoad(const sf::Vector2f &pos);
    // Adds traffic light, only to StraightRoadType Tiles
    void addTrafficLight(const sf::Vector2f &pos, unsigned int handler_id = UINT_MAX, float green_time = 5.f);
    // Implemented for easy tile removal with shift key
    EditingOption getEditingOption() { return editing_option_; }
    // Implemented for setting editing_option_ back after tile removal
    void setEditingOption(EditingOption opti) { editing_option_ = opti; }

private:
    Map &map_;
    const Window &window_;
    bool building_mode_ = true;
    EditingOption editing_option_ = Inspect;

    // This is Magic, dont ask :D
    union {
        int option_;
        RoadType road_option_;
        TemplateType template_option_;
        BuildingType building_option_;
    };

    // Stores highlighted tile, which was left clicked
    unsigned int selected_tile_index_ = UINT_MAX;
    // Stores highlighted tile, which is under mouse
    unsigned int hovered_tile_index_ = UINT_MAX;
    std::vector<unsigned int> hovered_tile_indices_;
    // Stores index of first added tile for slideAction()
    unsigned int start_tile_index_ = UINT_MAX;
    // Stores index of last added tile for slideAction()
    unsigned int last_tile_index_ = UINT_MAX;
    // Stores light which if highlighted tile has one
    TrafficLight *selected_light_ = nullptr;
    // This stores menu which gets opened when road is selected
    sf::Vector2i select_menu_pos_;

private:
    void addTemplate(const sf::Vector2f &pos);
    void removeItem(const sf::Vector2f &pos);
    void selectTile(const sf::Vector2f &pos);
    void unSelectTile();
    void connectRoad(Tile *tile);
    void connectRoads();
    void changeLightHandler(const sf::Vector2f &pos);
};
} // namespace ts