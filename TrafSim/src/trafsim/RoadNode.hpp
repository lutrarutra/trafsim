#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "trafsim/Road.hpp"

namespace TrafSim
{
class RoadNode
{
public:
    RoadNode(unsigned long long ref, const sf::Vector2f loc);
    RoadNode(unsigned long long ref, const sf::Vector2f loc, RoadNode &pervious);
    void connect(RoadNode &another_node);
    const std::vector<RoadNode *>& getNeighbors() const { return m_connections; }
    unsigned long long getRef() const { return m_ref; }
    sf::Vector2f getLocation() const;

public:
    static float DistanceBetween(const RoadNode &node1, const RoadNode &node2);

private:
    //TODO - can be const?
    std::vector<RoadNode *> m_connections;
    const sf::Vector2f m_loc;
    const unsigned long long m_ref;
};

} // namespace TrafSim
