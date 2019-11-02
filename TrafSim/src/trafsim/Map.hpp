#pragma once

#include <vector>
#include <memory>
#include <thread>


#include "core/Window.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    ~Map();
    void addEntity();
    void addEntities();
    // if somethings out side of the screen or zoomed out far we dont need to see it
    void updateVisible(const Window& window);
    // Draws everything on screen
    void draw(Window& window) const;
private:
    void checkVisible(const Window &window);
    //entities are stored as shared pointers in vector
public:
};

}; // namespace TrafSim