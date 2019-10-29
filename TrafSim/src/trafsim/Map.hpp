#pragma once

#include <vector>
#include <memory>
#include <thread>


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
    void showZoomed(const Window& window);
    // Draws everything on screen
    void draw(Window& window) const;
private:
    void checkVisible(const Window &window);
    //entities are stored as shared pointers in vector
    std::vector<std::unique_ptr<MapEntity>> m_entities;
    bool running = false;

public:
    //Prevents copy assignment
    Map &operator=(const Map &) = delete;
    //Prevents copying or deletes copy constructor
    Map(const Map &) = delete;
    std::thread t;
    mutable std::mutex vector_mutex;
};

}; // namespace TrafSim