#pragma once

#include <vector>
#include <memory>

#include "core/Window.hpp"
#include "MapEntity.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    ~Map();
    void addEntity(std::unique_ptr<MapEntity> &entity_ptr);
    void addEntities(std::vector<std::unique_ptr<MapEntity>> &entities);
    void showVisible(const Window& window);
    // Draws everything on screen
    void draw(Window& window) const;
private:
    //entities are stored as shared pointers in vector
    std::vector<std::unique_ptr<MapEntity>> m_entities;
public:
    //Prevents copy assignment
    Map &operator=(const Map &) = delete;
    //Prevents copying or deletes copy constructor
    Map(const Map &) = delete;
};

}; // namespace TrafSim