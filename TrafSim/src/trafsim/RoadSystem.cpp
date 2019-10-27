#include "trafsim/RoadSystem.hpp"

#include <algorithm>

namespace TrafSim
{

RoadSystem::RoadSystem(std::unique_ptr<std::vector<RoadNode>> &nodes, std::unique_ptr<std::vector<Road>> &roads)
    : m_nodes(nullptr), m_roadPoints(nullptr), m_roads(nullptr)
{
    nodes.swap(m_nodes);
    roads.swap(m_roads);
}

void RoadSystem::draw(Window &window) const
{
    for(const auto& road : *m_roads)
    {
        window.draw(road);
    }
}

} // namespace TrafSim