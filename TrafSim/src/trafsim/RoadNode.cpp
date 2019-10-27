#include "trafsim/RoadNode.hpp"

#include <math.h>
#include <algorithm>

namespace TrafSim
{

RoadNode::RoadNode(unsigned long long ref, const sf::Vector2f loc)
    : m_ref(ref), m_loc(loc)
{
}

RoadNode::RoadNode(unsigned long long ref, const sf::Vector2f loc, RoadNode &previous)
    : m_ref(ref), m_loc(loc)
{
    connect(previous);
}

sf::Vector2f RoadNode::getLocation() const
{
    return m_loc;
}

void RoadNode::connect(RoadNode &another_node)
{
    //Check if we have duplicate
    //TODO - is this necessary?
    if (std::find(m_connections.begin(), m_connections.end(), &another_node) == m_connections.end())
        m_connections.push_back(&another_node);
    if (std::find(another_node.m_connections.begin(), another_node.m_connections.end(), this) == another_node.m_connections.end())
        another_node.m_connections.push_back(this);
}

float RoadNode::DistanceBetween(const RoadNode &node1, const RoadNode &node2)
{
    sf::Vector2f v1 = node1.getLocation();
    sf::Vector2f v2 = node2.getLocation();
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

} // namespace TrafSim
