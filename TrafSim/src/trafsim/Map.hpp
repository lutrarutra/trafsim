#pragma once

#include <vector>
#include <memory>
#include <thread>


#include "core/Window.hpp"

#include "trafsim/DrawableEntity.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    ~Map();
    void addEntity(std::unique_ptr<DrawableEntity> &entity_ptr);
    void addEntities(std::vector<std::unique_ptr<DrawableEntity>> &entities);
    // if somethings out side of the screen or zoomed out far we dont need to see it
    void updateVisible(const Window& window);
    // Draws everything on screen
    void draw(Window& window) const;
private:
    void checkVisible(const Window &window);
    //entities are stored as shared pointers in vector
    std::vector<std::unique_ptr<DrawableEntity>> m_entities;
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