#pragma once

#include <vector>
#include <memory>
#include <thread>

#include "core/Window.hpp"
#include "util/VectorMath.hpp"
#include "trafsim/Road.hpp"
#include "trafsim/Car.hpp"

namespace TrafSim
{

// Map will be displayed to window with all it's elements
// Map will be zoomable with mousewheel and
class Map
{
public:
    Map();
    void createRoads(const std::shared_ptr<Node> begin);
    void draw(Window &window) const;
    void update(float delta_time);
    void checkIntersections();

private:
    // Constructs roads from nodes using recursive DFS algorithm to iterate over node graph
    void constructRoads(const std::shared_ptr<Node> &cur, std::shared_ptr<Road> prevRoad, std::map<std::shared_ptr<Node>, bool> &visited);

    std::vector<std::shared_ptr<Road>> m_roads;
    std::vector<Car> m_cars;
};

}; // namespace TrafSim