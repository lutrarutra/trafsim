#include "MapBuilder.hpp"

#include <string>
#include <memory>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

namespace ts
{

MapBuilder::MapBuilder(Map &map, const Window &window)
    : map_(map), window_(window)
{
    road_option_ = RoadType::StraightRoadType;
    building_option_ = BuildingType::HomeBuildingType;
}
// Outside of class static means that the function/variable is only visible in this file
// Kinda like private
static const char *editing_mode(EditingOption mode)
{
    return (const char *[]){
        "Inspect",
        "Add road",
        "Add building",
        "Add template",
        "Remove",
        "Rotate",
        "Flip",
        "Add light",
    }[mode];
}

static const char *building_type_name(BuildingType type)
{
    return (const char *[]){
        "Home Building",
        "Office Building",
    }[type];
}

static const char *road_type_name(RoadType type)
{
    return (const char *[]){
        "Straight Road",
        "Road Turn",
        "Intersection",
        "Trisection",
        "Road Junction",
        "Home Road",
    }[type];
}

const char *template_type_name(TemplateType type)
{
    return (const char *[]){
        "Cross Intersection",
        "T-intersection-down",
        "T-intersection-up",
        "T-intersection-left",
        "T-intersection-right",
        "Roundabout-left",
        "Roundabout-right",
    }[type];
}

void MapBuilder::drawGUI()
{
    if (!building_mode_)
        return;
    ImGui::Begin("Map Editor");

    // Choose click mode
    for (int i = 0; i != EditingOption::ModeCount; i++)
    {
        EditingOption mode = static_cast<EditingOption>(i);
        if (ImGui::RadioButton(editing_mode(mode), editing_option_ == mode))
        {
            editing_option_ = mode;
            option_ = 0;
        }
    }

    // Choose road type to add
    ImGui::BeginChild("Road type", ImVec2(0, 0), true);
    // Road type select
    if (editing_option_ == EditingOption::AddRoad)
    {
        ImGui::Text("Road type selected:");
        for (int i = 0; i < RoadType::RoadTypeCount; i++)
        {
            if (ImGui::RadioButton(road_type_name((RoadType)i), option_ == i))
                option_ = i;
        }
    }
    // Template type select
    else if (editing_option_ == EditingOption::AddTemplate)
    {
        ImGui::Text("Template selected:");
        for (int i = 0; i < TemplateType::TemplateTypeCount; i++)
        {
            if (ImGui::RadioButton(template_type_name((TemplateType)i), option_ == i))
                option_ = i;
        }
    }
    // Building type select
    else if (editing_option_ == EditingOption::AddBuilding)
    {
        ImGui::Text("Building selected:");
        for (int i = 0; i < BuildingType::BuildingTypeCount; i++)
        {
            if (ImGui::RadioButton(building_type_name((BuildingType)i), option_ == i))
                option_ = i;
        }
    }
    ImGui::EndChild();
    ImGui::End();

    // Left-click option menu
    if (selected_tile_index_ != UINT_MAX && map_.grid_.getTile(selected_tile_index_)->getCategory() == TileCategory::RoadCategory)
    {
        auto road_tile = static_cast<RoadTile *>(map_.grid_.getTile(selected_tile_index_));
        ImGui::SetNextWindowPos(select_menu_pos_);
        ImGui::Begin("Tile Editor");
        sf::Vector2i another_pos(select_menu_pos_.x, select_menu_pos_.y + ImGui::GetWindowHeight());
        ImGui::BeginColumns("", 2);
        RoadType selected_roadtype = road_tile->getType();
        for (int i = 0; i < RoadType::RoadTypeCount; i++)
        {
            RoadType road_type = static_cast<RoadType>(i);
            if (ImGui::RadioButton(road_type_name(road_type), selected_roadtype == road_type))
                addRoad(road_tile->getCenter(), road_type);
        }
        ImGui::NextColumn();
        if (ImGui::Button("Rotate"))
            rotateRoad(map_.grid_.getTile(selected_tile_index_)->getCenter());
        if (ImGui::Button("Flip"))
            flipRoad(map_.grid_.getTile(selected_tile_index_)->getCenter());
        if (ImGui::Button("Remove"))
            removeItem(map_.grid_.getTile(selected_tile_index_)->getCenter());
        // Traffic light editor
        ImGui::EndColumns();
        ImGui::End();
        ImGui::SetNextWindowPos(another_pos);
        ImGui::Begin("Traffic Light editor");
        if (road_tile && road_tile->getLight())
        {
            int time = road_tile->getLight()->green_time_;
            if (ImGui::SliderInt("Green time", &time, 0.f, 100.f, "%.0f"))
                road_tile->getLight()->green_time_ = time;
            if (ImGui::Button("Remove Light"))
            {
                map_.removeLight(road_tile->getLight());
                road_tile->removeLight();
            }
            if (ImGui::Button("New handler"))
            {
                map_.newLightNetwork(road_tile->getLight());
            }
            if (ImGui::Button("Change Handler"))
                selected_light_ = road_tile->getLight();
        }
        ImGui::End();
    }
}

void MapBuilder::addRoad(const sf::Vector2f &pos, RoadType type, bool autorotate)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getCategory() == BuildingCategory)
        return;

    // To check if there is already same type of road already.
    if (tile->getCategory() == RoadCategory)
    {
        auto road_tile = static_cast<RoadTile *>(tile);
        if (road_tile->getType() == type)
            return;
    }

    std::unique_ptr<Tile> road_tile;
    switch (type)
    {
    case StraightRoadType:
        road_tile = std::make_unique<StraightRoad>(*tile);
        break;
    case RoadTurnType:
        road_tile = std::make_unique<RoadTurn>(*tile);
        break;
    case IntersectionType:
        road_tile = std::make_unique<RoadIntersection>(*tile);
        break;
    case TrisectionType:
        road_tile = std::make_unique<RoadTrisection>(*tile);
        break;
    case JunctionType:
        road_tile = std::make_unique<RoadJunction>(*tile);
        break;
    case HomeRoadType:
        road_tile = std::make_unique<HomeRoad>(*tile);
        break;
    default:
        break;
    }
    // If there is road already a road we need to check if it has traffic light and then we need to remove it if yes
    if (tile->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *temp = static_cast<RoadTile *>(tile);
        if (temp->getLight())
        {
            map_.removeLight(temp->getLight());
            temp->removeLight();
        }
    }
    RoadTile *r = static_cast<RoadTile *>(road_tile.get());
    auto arr = map_.grid_.getNeigborTiles(tile->getTileIndex());
    if (autorotate)
        r->autoRotate(arr);

    map_.grid_.swapTile(road_tile);
    connectRoads();
    map_.updateClosestRoads();
}

void MapBuilder::addBuilding(const sf::Vector2f &pos, BuildingType type)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getCategory() != Empty)
        return;

    std::unique_ptr<Tile> building_tile;

    switch (type)
    {
    case OfficeBuildingType:
        building_tile = std::make_unique<OfficeBuilding>(*tile);
        break;
    case HomeBuildingType:
        building_tile = std::make_unique<HomeBuilding>(*tile);
        break;
    }

    BuildingTile *r = static_cast<BuildingTile *>(building_tile.get());
    auto arr = map_.grid_.getNeigborTiles(tile->getTileIndex());
    r->setId(map_.addBuilding(r));

    map_.grid_.swapTile(building_tile);
}

void MapBuilder::slideAction(const sf::Vector2f &pos, EditingOption option)
{
    // selected_tile_index_ is the left clicked tile
    // start_tile_index_ is used as a flag to initialize first roadtile rotation
    
    if(hovered_tile_index_ == selected_tile_index_)
    {
        start_tile_index_ = selected_tile_index_;

        auto start_neighbors = map_.grid_.getNeigborTiles(start_tile_index_);
      
        // CLEAN this mess ..
        // is there neighbors around start tile
        auto right_tile = map_.grid_.getTile(start_tile_index_ + 1);
        auto left_tile = map_.grid_.getTile(start_tile_index_ - 1);
        auto top_tile = map_.grid_.getTile(start_tile_index_ - map_.grid_.getSideCount());
        auto down_tile = map_.grid_.getTile(start_tile_index_ + map_.grid_.getSideCount());

        if ((right_tile && right_tile->getCategory() == RoadCategory)||
            (left_tile && left_tile->getCategory() == RoadCategory)||
            (top_tile && top_tile->getCategory() == RoadCategory)||
            (down_tile && down_tile->getCategory() == RoadCategory))
        {     
             start_tile_index_ = UINT_MAX;
        }
    }
    
    selected_tile_index_ = UINT_MAX;
    //start_tile_index_ = UINT_MAX;
    // Check if tile, which is hovered, hasnt changed since last frame
    if (hovered_tile_index_ == last_tile_index_)
        return;

    if (option == EditingOption::AddRoad)
    {
        // This first if statement initialize the first road tile direction
        // #1 first loop: will not get inside as last_tile_index_ == UINT_MAX
        // new road tile gets added at the end of this function ### add road tile
        // #2 second loop: will get inside as the last_tile_index_ == hovered_tile_index_
     
        if((start_tile_index_ != UINT_MAX) && (last_tile_index_ != UINT_MAX)){
                
            auto start_tile = map_.grid_.getTile(start_tile_index_);
            auto start_road = static_cast<RoadTile *>(start_tile);
            // if mouse moved down from start tile 
            if (hovered_tile_index_ - start_tile_index_ == map_.grid_.getSideCount())
            {
                // rotate road down
                start_road->rotate();
            }   
            // if mouse moved up from start tile 
            else if(start_tile_index_ - hovered_tile_index_ == map_.grid_.getSideCount()){
        
                // rotate road up
                start_road->flip();
                start_road->rotate();
            }
            // if mouse moved to left from start tile
            else if(start_tile_index_ - hovered_tile_index_ == 1){
                // rotate road left
                start_road->flip();
            }

            // first and last time to visit this if statement 
            start_tile_index_ = UINT_MAX;

        }
        else if (last_tile_index_ != UINT_MAX)
        {
            if (!map_.grid_.getTile(hovered_tile_index_) || map_.grid_.getTile(hovered_tile_index_)->getCategory() == RoadCategory)
                return;
            auto last_tile = map_.grid_.getTile(last_tile_index_);
            if (last_tile && last_tile->getCategory() == RoadCategory)
            {
                auto last_road = static_cast<RoadTile *>(last_tile);
                auto neighbors = map_.grid_.getNeigborTiles(last_tile_index_);
                if (last_road->getDir().x == 1)
                {
                    if (neighbors[RIGHT] && neighbors[RIGHT]->getTileIndex() != hovered_tile_index_)
                    {
                        addRoad(last_tile->getCenter(), RoadTurnType);
                        if (last_tile_index_ - hovered_tile_index_ == map_.grid_.getSideCount())
                        {
                            auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                            new_road->flip();
                        }
                    }
                }
                else if (last_road->getDir().x == -1)
                {
                    if (neighbors[LEFT] && neighbors[LEFT]->getTileIndex() != hovered_tile_index_)
                    {
                        addRoad(last_tile->getCenter(), RoadTurnType);
                        if (hovered_tile_index_ - last_tile_index_ == map_.grid_.getSideCount())
                        {
                            auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                            new_road->flip();
                        }
                    }
                }
                else if (last_road->getDir().y == 1)
                {
                    if (neighbors[UP] && neighbors[UP]->getTileIndex() != hovered_tile_index_)
                    {
                        addRoad(last_tile->getCenter(), RoadTurnType);
                        if (last_tile_index_ - hovered_tile_index_ == 1)
                        {
                            auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                            new_road->flip();
                        }
                    }
                }
                else if (last_road->getDir().y == -1)
                {
                    if (neighbors[DOWN] && neighbors[DOWN]->getTileIndex() != hovered_tile_index_)
                    {
                        addRoad(last_tile->getCenter(), RoadTurnType);
                        if (hovered_tile_index_ - last_tile_index_ == 1)
                        {
                            auto new_road = static_cast<RoadTile *>(map_.grid_.getTile(last_tile_index_));
                            new_road->flip();
                        }
                    }
                }
            }
        }
        // ### add road tile
        addRoad(pos, StraightRoadType);
        
    }
    else if (option == EditingOption::Remove)
    {
        if (map_.grid_.getTile(hovered_tile_index_) && map_.grid_.getTile(hovered_tile_index_)->getCategory() == TileCategory::RoadCategory)
        {
            removeItem(map_.grid_.getTile(hovered_tile_index_)->getCenter());
        }
        else if (map_.grid_.getTile(hovered_tile_index_) && map_.grid_.getTile(hovered_tile_index_)->getCategory() == TileCategory::BuildingCategory)
        {
            removeItem(map_.grid_.getTile(hovered_tile_index_)->getCenter());
        }
    }

    last_tile_index_ = hovered_tile_index_;
}

void MapBuilder::addTrafficLight(const sf::Vector2f &pos, unsigned int handler_id, float green_time)
{
    auto tile = map_.grid_.getTile(pos);
    // Traffic light only can be on staright road type
    if (!tile || tile->getCategory() == RoadCategory)
        if (static_cast<RoadTile *>(tile)->getType() != RoadType::StraightRoadType)
            return;

    RoadTile *road = static_cast<RoadTile *>(tile);
    if (road->getLight())
        return;
    if (handler_id == UINT_MAX)
        road->addLight(map_.getCurrentNetworkId(), green_time);
    else
        road->addLight(handler_id, green_time);
    map_.addLight(road->getLight(), road->getLight()->getHandlerId());
}

void MapBuilder::addTemplate(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile)
        return;

    if (IntersectionTemplates::CanPlace(template_option_, tile->getTileIndex(), map_.grid_.getSideCount()))
    {
        map_.newLightNetwork();
        auto tiles_to_add = IntersectionTemplates::GetTiles(template_option_, tile->getTileIndex(), map_.grid_.getSideCount());
        for (auto tile_info : tiles_to_add)
        {
            addRoad(map_.grid_.getTile(tile_info.index)->getCenter(), tile_info.type, false);
            RoadTile *road_tile = static_cast<RoadTile *>(map_.grid_.getTile(tile_info.index));
            if (tile_info.dir.x == -1)
            {
                rotateRoad(road_tile->getCenter());
                rotateRoad(road_tile->getCenter());
            }
            else if (tile_info.dir.y == 1)
            {
                rotateRoad(road_tile->getCenter());
                rotateRoad(road_tile->getCenter());
                rotateRoad(road_tile->getCenter());
            }
            else if (tile_info.dir.y == -1)
            {
                rotateRoad(road_tile->getCenter());
            }
            if (tile_info.flipped)
                road_tile->flip();
            if (tile_info.hasLight)
                addTrafficLight(road_tile->getCenter());
        }
    }
}

void MapBuilder::removeItem(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);

    if (!tile)
        return;

    if (tile->getCategory() == TileCategory::RoadCategory)
    {
        RoadTile *road = static_cast<RoadTile *>(tile);

        if (road->getLight())
        {
            map_.removeLight(road->getLight());
        }

        std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
        map_.grid_.swapTile(empty_tile);
        connectRoads();
    }
    else if (tile->getCategory() == TileCategory::BuildingCategory)
    {

        BuildingTile *building = static_cast<BuildingTile *>(tile);
        map_.removeBuilding(building->getId());
        std::unique_ptr<Tile> empty_tile = std::make_unique<Tile>(tile->getPos(), tile->getSize(), tile->getTileIndex());
        map_.grid_.swapTile(empty_tile);
    }
}

void MapBuilder::rotateRoad(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getCategory() != TileCategory::RoadCategory)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile);
    road_tile->rotate();
    connectRoads();
}

void MapBuilder::flipRoad(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getCategory() != TileCategory::RoadCategory)
        return;

    RoadTile *road_tile = static_cast<RoadTile *>(tile);
    road_tile->flip();
    connectRoads();
}

void MapBuilder::connectRoad(Tile *tile)
{
    // TODO - Do we need to disconnect empty tiles when clearing?
    if (tile && tile->getCategory() == TileCategory::RoadCategory)
    {
        tile->getNode()->disconnectAll();
        RoadTile *road_tile = static_cast<RoadTile *>(tile);
        auto arr = map_.grid_.getNeigborTiles(tile->getTileIndex());
        road_tile->connect(arr);
    }
}

void MapBuilder::connectRoads()
{
    for (unsigned int i = 0; i < map_.grid_.getTotalTileCount(); ++i)
    {
        auto tile = map_.grid_.getTile(i);
        connectRoad(tile);
    }
}

void MapBuilder::changeLightHandler(const sf::Vector2f &pos)
{
    auto tile = map_.grid_.getTile(pos);
    if (!tile || tile->getCategory() == TileCategory::RoadCategory)
        if (static_cast<RoadTile *>(tile)->getType() != RoadType::StraightRoadType)
            return;
    RoadTile *new_light_tile = static_cast<RoadTile *>(tile);
    TrafficLight *new_light = new_light_tile->getLight();
    if (new_light_tile->getLight())
    {
        map_.removeLight(selected_light_);
        selected_light_->setHandlerId(new_light->getHandlerId());
        map_.addLight(selected_light_, new_light->getHandlerId());
    }
    selected_light_ = nullptr;
}

void MapBuilder::clearMap()
{
    map_.clearMap();
    connectRoads();
}
/*
*   Builder input
*/

void MapBuilder::selectTile(const sf::Vector2f &pos)
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
        select_menu_pos_ = window_.convert(new_tile->getPos() + sf::Vector2f(new_tile->getSize(), 0.f));
    }
}

void MapBuilder::unSelectTile()
{
    if (selected_tile_index_ != UINT_MAX)
        map_.grid_.getTile(selected_tile_index_)->unSelectTile();
    selected_tile_index_ = UINT_MAX;
}

void MapBuilder::setBuildingMode(bool val)
{
    if (building_mode_ == val)
        return;
    building_mode_ = val;
    editing_option_ = Inspect;
    road_option_ = RoadType::StraightRoadType;
    selected_tile_index_ = UINT_MAX;
    hovered_tile_index_ = UINT_MAX;
    selected_light_ = nullptr;
}

void MapBuilder::handleInput(const sf::Event &ev)
{
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (window_.isGuiHovered())
            return;
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        if (ev.mouseButton.button == sf::Mouse::Right)
        {
            if (selected_light_)
            {
                changeLightHandler(pos);
            }
            switch (editing_option_)
            {
            case AddRoad:
                addRoad(pos, road_option_);
                break;
            case AddBuilding:
                addBuilding(pos, building_option_);
                break;
            case AddTemplate:
                addTemplate(pos);
                break;
            case Remove:
                removeItem(pos);
                break;
            case Rotate:
                rotateRoad(pos);
                break;
            case Flip:
                flipRoad(pos);
                break;
            case AddLight:
                addTrafficLight(pos);
                break;
            default:
                break;
            }
            unSelectTile();
        }
        else if (ev.mouseButton.button == sf::Mouse::Left)
        {
            selectTile(pos);
        }
    }
    else if (ev.type == sf::Event::MouseMoved)
    {
        sf::Vector2f pos = window_.convert(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y));
        auto new_tile = map_.grid_.getTile(pos);
        if (!new_tile)
            return;
        if (hovered_tile_index_ == new_tile->getTileIndex())
            return;
        hovered_tile_index_ = new_tile->getTileIndex();
        for (auto it = hovered_tile_indices_.begin(); it != hovered_tile_indices_.end(); ++it)
        {
            if (map_.grid_.getTile(*it))
                map_.grid_.getTile(*it)->unSelectTile();
        }
        hovered_tile_indices_.clear();
        if (editing_option_ == EditingOption::AddTemplate)
        {
            auto vec = IntersectionTemplates::GetTiles(template_option_, new_tile->getTileIndex(), map_.grid_.getSideCount());
            hovered_tile_indices_.reserve(vec.size());
            for (auto tile_info : vec)
            {
                if (map_.grid_.getTile(tile_info.index))
                {
                    map_.grid_.getTile(tile_info.index)->hoverTile();
                    hovered_tile_indices_.emplace_back(tile_info.index);
                }
            }
        }
        else
        {
            new_tile->hoverTile();
            hovered_tile_indices_.emplace_back(new_tile->getTileIndex());
        }
    }
    else if (ev.type == sf::Event::MouseButtonReleased)
    {
        last_tile_index_ = UINT_MAX;
    }
}
} // namespace ts
