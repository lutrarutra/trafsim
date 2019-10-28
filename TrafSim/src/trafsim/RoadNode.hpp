#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace TrafSim
{
class RoadNode
{
public:
    RoadNode(unsigned long long ref, const sf::Vector2f loc);
    RoadNode(unsigned long long ref, const sf::Vector2f loc, std::shared_ptr<RoadNode> &another);
    void connect(std::shared_ptr<RoadNode> &another);
    const std::vector<std::shared_ptr<RoadNode>>& getNeighbors() const { return m_neighbors; }
    unsigned long long getRef() const { return m_ref; }
    float distanceToPoint(const sf::Vector2f &point) const;
    sf::Vector2f getLocation() const;

public:
    // TODO - I Dont think this is necessary
    //static float DistanceBetween(const RoadNode &node1, const RoadNode &node2);

private:
    std::vector<std::shared_ptr<RoadNode>> m_neighbors;
    const sf::Vector2f m_loc;
    const unsigned long long m_ref;
};

} // namespace TrafSim
