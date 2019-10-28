#include "trafsim/RoadSystem.hpp"

#include <algorithm>

namespace TrafSim
{

const std::shared_ptr<RoadNode> RoadSystem::closestNode(const sf::Vector2f loc) const
{
    std::shared_ptr<RoadNode> closest = m_roads[0]->getNodes()[0];
    // float distance = __FLT_MAX__;
    // for (const auto &road : m_roads)
    // {
    //     float dist1 = road->getLine().m_start->distanceToPoint(loc);
    //     float dist2 = road->getLine().m_end->distanceToPoint(loc);
    //     if (distance > dist1)
    //     {
    //         distance = dist1;
    //         closest = road->getLine().m_start;
    //     }
    //     if (distance > dist2)
    //     {
    //         distance = dist2;
    //         closest = road->getLine().m_end;
    //     }
    // }
    return closest;
}

// void RoadSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
// {
//     //PerformanceTimer p;
//     //Now it's faster to draw std::vector<sf::Vertex> instread of sf::VertexBuffer
//     target.draw(&m_vertices[0], m_vertices.size(), sf::Lines, states);
// }

} // namespace TrafSim