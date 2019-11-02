#pragma once

#include <vector>
#include <memory>
#include <thread>


#include "core/Window.hpp"
#include "util/VectorUtil.hpp"
#include "trafsim/Road.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    void createRoads(const std::vector<std::shared_ptr<Node>> &nodes);
    void draw(Window& window) const;
private:
    std::vector<Road> m_roads;
};

}; // namespace TrafSim