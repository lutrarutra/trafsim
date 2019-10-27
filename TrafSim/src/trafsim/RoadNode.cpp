#include "trafsim/RoadNode.hpp"

#include <math.h>
#include <algorithm>

namespace TrafSim
{

RoadNode::RoadNode(unsigned long long ref, const sf::Vector2f loc)
    : m_ref(ref), m_loc(loc)
{
}

RoadNode::RoadNode(unsigned long long ref, const sf::Vector2f loc, std::shared_ptr<RoadNode> &another)
    : m_ref(ref), m_loc(loc)
{
    connect(another);
}

float RoadNode::distanceToPoint(const sf::Vector2f &point) const
{
    return sqrt(pow(point.x - m_loc.x, 2) + pow(point.y - m_loc.y, 2));
}

sf::Vector2f RoadNode::getLocation() const
{
    return m_loc;
}

void RoadNode::connect(std::shared_ptr<RoadNode> &another)
{
    //Check if we have duplicate
    //TODO - is duplicate pair possible to be pushed here?
    m_neighbors.push_back(another);
    another->m_neighbors.push_back(std::make_unique<RoadNode>(*this));
}

// float RoadNode::DistanceBetween(const RoadNode &node1, const RoadNode &node2)
// {
//     sf::Vector2f v1 = node1.getLocation();
//     sf::Vector2f v2 = node2.getLocation();
//     return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
// }

} // namespace TrafSim
