#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Window.hpp"
#include "MapEntity.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    void addEntity(std::shared_ptr<MapEntity> entity_ptr);
    // Draws everything on screen
    void draw(Window& window) const;
private:
    //entities are stored as shared pointers in vector
    std::vector<std::shared_ptr<MapEntity>> m_entities;
public:
    //Prevents copy assignment
    Map &operator=(const Map &) = delete;
    //Prevents copying or deletes copy constructor
    Map(const Map &) = delete;
};

}; // namespace TrafSim