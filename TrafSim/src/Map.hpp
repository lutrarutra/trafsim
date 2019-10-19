#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

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
    ~Map();
    void zoom(int z);
    void load_objects();
    // Draws everything on screen
    void draw(Window& window) const;
private:
    std::vector<MapEntity> entities_;
    int zoom_;
public:
    //Prevents copy assignment
    Map &operator=(const Map &) = delete;
    //Prevents copying or deletes copy constructor
    Map(const Map &) = delete;
};

}; // namespace TrafSim