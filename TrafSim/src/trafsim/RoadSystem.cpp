#include "trafsim/RoadSystem.hpp"

#include <algorithm>

namespace TrafSim
{

RoadSystem::RoadSystem(std::vector<std::shared_ptr<RoadNode>> &nodes, std::unique_ptr<std::vector<Road>> &roads)
    : m_roads(nullptr)
{
    m_nodes = std::move(nodes);
    roads.swap(m_roads);
    //1185 nodes from tammisalo.osm
    //std::cout << m_nodes->size() << "\n";
}

const std::shared_ptr<RoadNode> RoadSystem::closestNode(const sf::Vector2f loc) const
{
    std::shared_ptr<RoadNode> closest = m_nodes[0];
    float distance = __FLT_MAX__;
    for (const auto node : m_nodes)
    {
        float dist = node->distanceToPoint(loc);
        if (distance > dist)
        {
            distance = dist;
            closest = node;
        }
    }
    return closest;
}

void RoadSystem::draw(Window &window) const
{
    for (const auto &road : *m_roads)
    {
        window.draw(road);
    }
}

} // namespace TrafSim